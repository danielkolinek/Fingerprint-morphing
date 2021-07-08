"""
   	Morphing of Fingerprints
    File:   alighnOrientFields.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements fingerprint alignment by orientation fields

    Code for alignment inspired by paper: On the Feasibility of Creating Double-Identity Fingerprints
    [Online at: https://ieeexplore.ieee.org/document/7782346].
    Version: 1.0
"""
import numpy as np
import cv2
import math
from scipy.ndimage.interpolation import rotate

def moveFingerprint(orientation_field, block_size, transformStep, axis, value=0):
    # roll image in direction
    blockStep = block_size*transformStep
    rolled = np.roll(orientation_field, blockStep, axis)

    # zero edges
    height, width = orientation_field.shape
    if axis == 0:
        zeros = np.zeros((abs(blockStep), width))
        ones =  np.ones((height-abs(blockStep), width))
        if transformStep > 0:
            mask = np.vstack([zeros,ones])
        else:
            mask = np.vstack([ones, zeros])
    else:
        zeros = np.zeros((height, abs(blockStep)))
        ones =  np.ones((height, width-abs(blockStep)))
        if transformStep > 0:
            mask = np.hstack([zeros,ones])
        else:
            mask = np.hstack([ones, zeros])
    
    rolled = rolled*mask

    # add to edges value if needed 
    if value != 0:
        mask = np.where(mask==0, 255, 0)
        rolled = rolled+mask
    return rolled

# gets fingerprint object and returns rotated img, mask and smoothedorientationfield
def rotateEverything(fingerprint, angle):
    if angle == 0: return fingerprint.fingerprint, fingerprint.mask, fingerprint.orientation_field, fingerprint.smooth_orientation_field, fingerprint.normalized_b_w
    #create copy of eveything
    degimg = np.copy(fingerprint.fingerprint)
    degmask = np.copy(fingerprint.mask)
    degnormalized = np.copy(fingerprint.normalized_b_w)
    #compute
    degimg = rotate(degimg, angle=angle, cval=255)
    degnormalized = rotate(degnormalized, angle=angle, cval=255)
    degmask = rotate(degmask, angle=angle, cval=0)
    orientation , smoooth, _ = fingerprint.getOrientationField(degimg, fingerprint.block_size, degmask)
    return degimg, degmask, orientation, smoooth, degnormalized

# adds rows or colls to array if is smaller then shape  
def upshape(array, shape, value=0):
    # resize orientation field to get same or fields if is bigger
    if array.shape[0] < shape[0]:# height < bigger height
        overfitting_part = shape[0] - array.shape[0]
        bottom = np.ones((overfitting_part, array.shape[1]))*value
        tmp = np.copy(array)
        array = np.vstack([array, bottom])
    if array.shape[1] < shape[1]:# width < bigger width
        overfitting_part = shape[1] - array.shape[1]
        right = np.ones((array.shape[0], overfitting_part))*value
        array = np.hstack([array, right])
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
def alighn(fingerprint_1, fingerprint_2, step_size=2, minvr=0.3, angle_step=15):
    block_size = fingerprint_1.block_size
    angle_range = 45

    # get all possible rotations of seond fingerprint
    print('Aligning process: ', flush=False)
    allRotations = []
    perc = 0
    for angle in range(-angle_range, angle_range, angle_step):    #30, 360, 30
        _, _, _, ori, _ = rotateEverything(fingerprint_2, angle)
        allRotations.append(ori)
        # perc to print
        perc += angle_step
        print('Orientation fields: ', int(perc/(angle_range*2)*100), "%", end="\r", flush=True)
    print(flush=False)
    # alighn all possible
    steps_height, steps_width = fingerprint_1.fingerprint.shape
    # (-half; half)
    steps_width = int((steps_width/5)/(block_size))
    steps_height = int((steps_height/5)/(block_size))

    max_s = 0
    max_pos = (0,0)
    max_angle = 0
    actual_angle = -angle_range

    iteration = 0
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
                multiplied = moved_or_field * fingerprint_1.smooth_orientation_field
                multiplied_non_zero = np.count_nonzero(multiplied)
                align_cover = multiplied_non_zero / fingerprint_1.non_zero_orientation_field_count
                if  align_cover  < minvr:
                    break
                
                # just for now
                r1 = 1
                r2 = 1

                # compute S(O1,O2) alignment
                actual_s = np.sum(
                        np.where(
                            np.logical_and(fingerprint_1.smooth_orientation_field!=0, moved_or_field!=0), 
                            (r1+r2)*(1-(2*abs(fingerprint_1.smooth_orientation_field-moved_or_field))/math.pi),
                            0)
                    )/(r1*multiplied_non_zero+r2*multiplied_non_zero)
                if max_s < actual_s:
                    max_s = actual_s
                    max_angle = actual_angle
                    max_pos = (x, y)  
                """
                if actual_angle == 0 and x==0 and y==0:
                    print(flush=False)
                    print(actual_s)
                    cv2.imshow("origo", fingerprint_1.drawOrientationField(fingerprint_1.orientation_field,block_size))
                    cv2.imshow("moved", fingerprint_1.drawOrientationField(moved_or_field,block_size))
                    cv2.waitKey(0)
                    cv2.destroyAllWindows()
                """
                    
        print('Aligning orientation fields: ',int((iteration)/(len(allRotations)-1)*100), "%", end="\r", flush=True)
        actual_angle += angle_step 
        iteration+=1
        
    print(flush=False)
    print("Best alighnment S value is: ", "{:.2f}".format(max_s*100), "% for angle: ", max_angle, "° and moved position by: ", max_pos)

    # example how to move field based on returned value
    """
    moved_or_field = moveFingerprint(allRotations[int(max_angle/30)], block_size, max_pos[0], 0)
    moved_or_field = np.array(moveFingerprint(moved_or_field, block_size, max_pos[1], 1))
    cv2.imshow("Test", fingerprint_1.drawOrientationField(moved_or_field, block_size))
    """

    return max_pos, max_angle

def cutIntersections(fingerprint_1, fingerprint_2):
    print("Getting interections")
    # masks intersection
    mask_intersection = np.where(np.logical_and(fingerprint_1.mask != False, fingerprint_2.mask != False), 1.0, 0.0)
    mask_intersection = cv2.GaussianBlur(mask_intersection,(5,5), 1)
    fingerprint_1.mask = fingerprint_2.mask = mask_intersection
    # fingerprint img intersection
    fingerprint_1.fingerprint = np.where(mask_intersection != 0, fingerprint_1.fingerprint, 255)
    fingerprint_2.fingerprint = np.where(mask_intersection != 0, fingerprint_2.fingerprint, 255)
    # orientationfields intersection
    fingerprint_1.orientation_field = np.where(np.logical_and(fingerprint_1.orientation_field != 0, fingerprint_2.orientation_field != 0), fingerprint_1.orientation_field, 0)
    fingerprint_2.orientation_field = np.where(np.logical_and(fingerprint_1.orientation_field != 0, fingerprint_2.orientation_field != 0), fingerprint_2.orientation_field, 0)
    # smoothed orientationfields intersection
    fingerprint_1.smooth_orientation_field = np.where(np.logical_and(fingerprint_1.smooth_orientation_field != 0, fingerprint_2.smooth_orientation_field != 0), fingerprint_1.smooth_orientation_field, 0)
    fingerprint_2.smooth_orientation_field = np.where(np.logical_and(fingerprint_1.smooth_orientation_field != 0, fingerprint_2.smooth_orientation_field != 0), fingerprint_2.smooth_orientation_field, 0)