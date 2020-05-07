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

# Find the best alighn of two fingerprint by comparing their orientation field
# returns:
#  - baskkground = bigger image index (if fingerprint1.orientationfield is bigger, then returns 0.)
#  - (x,y) = position of best alignment
#  - Phi = angle of alignment 
def alighn(fingerprint_1, fingerprint_2, step_size=2, minvr=0.5, angle_step=30):
    # fingerprints to array for easyier work
    fingerprins = [fingerprint_1, fingerprint_2]
    block_size = fingerprint_1.block_size

    # get which one is bigger 
    vo_non_zero_max = 0 if fingerprint_1.non_zero_orientation_field_count > fingerprint_2.non_zero_orientation_field_count else 1
    second = int((vo_non_zero_max+1)/2)
    #print(fingerprins[vo_non_zero_max].non_zero_orientation_field_count)
    
    # get all possible rotations
    print('Started counting orientation fields: ', flush=False)
    allRotations = [fingerprins[vo_non_zero_max].orientation_field]
    for angle in range(30, 180, angle_step):    #30, 360, 30
        degimg = rotate(fingerprins[vo_non_zero_max].fingerprint, angle=angle, cval=255)
        degmask = rotate(fingerprins[vo_non_zero_max].mask, angle=angle, cval=0)
        degmask = np.where(degmask >200, 255, 0)
        ori, _, _ = fingerprint_1.getOrientationField(degimg, block_size, degmask)
        allRotations.append(ori)
        print('Orientation field for', angle, end="\r", flush=True)
    print(flush=False)
    # alighn all possible
    steps_height, steps_width = fingerprins[vo_non_zero_max].fingerprint.shape
    # (-half; half)
    steps_width = int((steps_width/2)/(block_size))
    steps_height = int((steps_height/2)/(block_size))

    max_s = 0
    max_pos = (0,0)
    max_angle = 0
    actual_angle = 0

    print('Aligning proccess started:', flush=False)
    for rotation in allRotations:
        for y in range(-steps_height, steps_width, step_size):
            for x in range(-steps_width, steps_width,step_size):
                # move orientation field
                moved_or_field = moveFingerprint(rotation, block_size, x, 0)
                moved_or_field = np.array(moveFingerprint(moved_or_field, block_size, y, 1))

                # resize orientation field to get same or fields
                if moved_or_field.shape[0] < fingerprins[vo_non_zero_max].orientation_field.shape[0]:# height < bigger height
                    overfitting_part = fingerprins[vo_non_zero_max].orientation_field.shape[0] - moved_or_field.shape[0]
                    bottom = np.zeros((overfitting_part, moved_or_field.shape[1]))
                    moved_or_field = np.vstack([moved_or_field, bottom])
                elif moved_or_field.shape[0] > fingerprins[vo_non_zero_max].orientation_field.shape[0]: #height > than bigger height
                    overfitting_part =  moved_or_field.shape[0] - fingerprins[vo_non_zero_max].orientation_field.shape[0]
                    moved_or_field = moved_or_field[:-overfitting_part,:]

                if moved_or_field.shape[1] < fingerprins[vo_non_zero_max].orientation_field.shape[1]:# width < bigger width
                    overfitting_part = fingerprins[vo_non_zero_max].orientation_field.shape[1] - moved_or_field.shape[1]
                    bottom = np.zeros((moved_or_field.shape[0], overfitting_part))
                    moved_or_field = np.hstack([moved_or_field, bottom])
                elif moved_or_field.shape[1] > fingerprins[vo_non_zero_max].orientation_field.shape[1]: #width is lower than bigger width
                    overfitting_part =  moved_or_field.shape[1] - fingerprins[vo_non_zero_max].orientation_field.shape[1]
                    moved_or_field = moved_or_field[:,:-overfitting_part]

                # check min alighment rule
                multiplied = moved_or_field * fingerprins[vo_non_zero_max].orientation_field
                multiplied_non_zero = np.count_nonzero(multiplied)
                align_cover = multiplied_non_zero / fingerprins[vo_non_zero_max].non_zero_orientation_field_count
                if  align_cover  < minvr:
                    break
                
                # just for now
                r1 = 1
                r2 = 1

                # compute S(O1,O2) alignment
                actual_s = np.sum(
                    np.where(
                        multiplied != 0, 
                        (r1+r2)*(1-(2*abs(fingerprins[vo_non_zero_max].orientation_field-moved_or_field))/math.pi),
                        0)
                )/(r1*multiplied_non_zero+r2*multiplied_non_zero)
                
                if max_s < actual_s:
                    max_s = actual_s
                    max_angle = actual_angle
                    max_pos = (x, y)  
                    #cv2.imshow("OKOK", fingerprint_1.drawOrientationField(fingerprint_1.fingerprint, moved_or_field, block_size))
                    #cv2.waitKey(0)
                    #cv2.destroyAllWindows()
        print('Alighning for angle ', actual_angle, end="\r", flush=True)
        actual_angle += angle_step 
        
    print(flush=False)
    print("Best alighnment S value is: ", max_s)


    moved_or_field = moveFingerprint(fingerprins[second].orientation_field, block_size, max_pos[0], 0)
    moved_or_field = np.array(moveFingerprint(moved_or_field, block_size, max_pos[1], 1))
    cv2.imshow("OKOK", fingerprint_1.drawOrientationField(fingerprint_1.fingerprint, moved_or_field, block_size))

    return max_s, max_angle, max_pos