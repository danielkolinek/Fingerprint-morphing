import numpy as np
import cv2
import math
from scipy.ndimage.interpolation import rotate

def moveFingerprint(fingerprint, transformStep, axis):
    # roll image in direction
    blockStep = fingerprint.blocksize*transformStep
    rolled = np.roll(fingerprint.orientation_field, blockStep, axis)
    
    height, width = fingerprint.orientation_field.shape
    if axis == 0:
        zeros = np.zeros((fingerprint.blocksize, width))
        ones =  np.ones((height-fingerprint.blocksize, width))
        if transformStep > 0:
            mask = np.vstack([zeros,ones])
        else:
            mask = np.vstack([ones, zeros])
    else:
        zeros = np.zeros((height, fingerprint.blocksize))
        ones =  np.ones((height, width-fingerprint.blocksize))
        if transformStep > 0:
            mask = np.hstack([zeros,ones])
        else:
            mask = np.hstack([ones, zeros])

    return rolled*mask

def alighn(fingerprint_1, fingerprint_2):
    block_size = fingerprint_1.block_size
    # get 
    vo_1_not_zero = np.count_nonzero(fingerprint_1.orientation_field)
    vo_2_not_zero = np.count_nonzero(fingerprint_2.orientation_field)
    print(vo_1_not_zero)
    print(vo_2_not_zero)
    


    gray_s = fingerprint_1.fingerprint
    orientation_field_s = fingerprint_1.orientation_field
    mask_s = fingerprint_1.mask
    # get all possible rotations
    allRotations = [orientation_field_s]
    for angle in range(30, 60, 30):    #30, 360, 30
        degimg = rotate(gray_s, angle=angle, cval=255)
        degmask = rotate(mask_s, angle=angle, cval=0)
        degmask = np.where(degmask >200, 255, 0)
        ori, _, _ = fingerprint_1.getOrientationField(degimg, block_size, degmask)
        allRotations.append(ori)
        print("Orientation field ", angle, " just done.")
    # alighn all possible 
    
    return 