import numpy as np
import cv2
import math
from scipy.ndimage.interpolation import rotate

def moveFingerprint(orientation_field, block_size, transformStep, axis):
    # roll image in direction
    blockStep = block_size*transformStep
    rolled = np.roll(orientation_field, blockStep, axis)
    
    height, width = orientation_field.shape
    if axis == 0:
        zeros = np.zeros((block_size, width))
        ones =  np.ones((height-block_size, width))
        if transformStep > 0:
            mask = np.vstack([zeros,ones])
        else:
            mask = np.vstack([ones, zeros])
    else:
        zeros = np.zeros((height, block_size))
        ones =  np.ones((height, width-block_size))
        if transformStep > 0:
            mask = np.hstack([zeros,ones])
        else:
            mask = np.hstack([ones, zeros])

    return rolled*mask

# gets fingerprint object and returns rotated img, mask and smoothedorientationfield
def rotateEverything(fingerprint, angle):
    #create copy of eveything
    degimg = np.copy(fingerprint.fingerprint)
    degmask = np.copy(fingerprint.mask)
    #compute
    degimg = rotate(degimg, angle=angle, cval=255)
    degmask = rotate(degmask, angle=angle, cval=0)
    degmask = np.where(degmask >200, 255, 0)
    _ , ori, _ = fingerprint.getOrientationField(degimg, fingerprint.block_size, degmask)
    return degimg, degmask, ori

# adds rows or colls to array if is smaller then shape  
def upshape(array, shape):
    # resize orientation field to get same or fields if is bigger
    if array.shape[0] < shape[0]:# height < bigger height
        overfitting_part = shape[0] - array.shape[0]
        bottom = np.zeros((overfitting_part, array.shape[1]))
        array = np.vstack([array, bottom])

    if array.shape[1] < shape[1]:# width < bigger width
        overfitting_part = shape[1] - array.shape[1]
        bottom = np.zeros((array.shape[0], overfitting_part))
        array = np.hstack([array, bottom])
    
    return array

# removes rows or colls if array is bigger then shape
def downshape(array, shape):
    # resize orientation field to get same or fields if is smaller
    if array.shape[0] > shape[0]: #height > than bigger height
        overfitting_part =  array.shape[0] - shape[0]
        array = array[:-overfitting_part,:]
    if array.shape[1] > shape[1]: #width is lower than bigger width
        overfitting_part =  array.shape[1] - shape[1]
        array = array[:,:-overfitting_part]

    return array

# Find the best alighn of two fingerprint by comparing their orientation field
# returns:
#  - baskkground = bigger image index (if fingerprint1.orientationfield is bigger, then returns 0.)
#  - (x,y) = position of best alignment
#  - Phi = angle of alignment 
def alighn(fingerprint_1, fingerprint_2, step_size=2, minvr=0.3, angle_step=30):
    block_size = fingerprint_1.block_size
    angle_range = 360

    # get all possible rotations of seond fingerprint
    print('Aligning process: ', flush=False)
    allRotations = [fingerprint_2.orientation_field]
    for angle in range(angle_step, angle_range, angle_step):    #30, 360, 30
        _, _, ori = rotateEverything(fingerprint_2, angle)
        allRotations.append(ori)
        print('Orientation fields: ', int(angle/(angle_range-angle_step)*100), "%", end="\r", flush=True)
    print(flush=False)
    # alighn all possible
    steps_height, steps_width = fingerprint_1.fingerprint.shape
    # (-half; half)
    steps_width = int((steps_width/2)/(block_size))
    steps_height = int((steps_height/2)/(block_size))

    max_s = 0
    max_pos = (0,0)
    max_angle = 0
    actual_angle = 0

    for rotation in allRotations:
        #upshape
        rotation = upshape(rotation, fingerprint_1.orientation_field.shape)

        for y in range(-steps_height, steps_width, step_size):
            for x in range(-steps_width, steps_width,step_size):

                # move orientation field
                moved_or_field = moveFingerprint(rotation, block_size, x, 0)
                moved_or_field = np.array(moveFingerprint(moved_or_field, block_size, y, 1))
                
                # downshape
                moved_or_field = downshape(moved_or_field, fingerprint_1.orientation_field.shape)

                # check min alighment rule
                multiplied = moved_or_field * fingerprint_1.orientation_field
                multiplied_non_zero = np.count_nonzero(multiplied)
                align_cover = multiplied_non_zero / fingerprint_1.non_zero_orientation_field_count
                if  align_cover  < minvr:
                    #print(align_cover)
                    break
                
                # just for now
                r1 = 1
                r2 = 1

                # compute S(O1,O2) alignment
                actual_s = np.sum(
                    np.where(
                        multiplied != 0, 
                        (r1+r2)*(1-(2*abs(fingerprint_1.orientation_field-moved_or_field))/math.pi),
                        0)
                )/(r1*multiplied_non_zero+r2*multiplied_non_zero)
                if max_s < actual_s:
                    max_s = actual_s
                    max_angle = actual_angle
                    max_pos = (x, y)  

                """
                cv2.imshow("OKOK", fingerprint_1.drawOrientationField(moved_or_field,block_size))
                cv2.waitKey(0)
                cv2.destroyAllWindows()
                """
                    
        print('Alighning process: ',int(actual_angle/(angle_range-angle_step)*100), "%", end="\r", flush=True)
        actual_angle += angle_step 
        
    print(flush=False)
    print("Best alighnment S value is: ", max_s, " for angle: ", max_angle, " and position: ", max_pos)

    # example how to move field based on returned value
    """
    moved_or_field = moveFingerprint(allRotations[int(max_angle/30)], block_size, max_pos[0], 0)
    moved_or_field = np.array(moveFingerprint(moved_or_field, block_size, max_pos[1], 1))
    cv2.imshow("Test", fingerprint_1.drawOrientationField(moved_or_field, block_size))
    """

    return max_pos, max_angle