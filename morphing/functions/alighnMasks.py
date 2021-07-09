"""
   	Morphing of Fingerprints
    File:   alighnOrientFields.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements fingerprint alignment by masks

    Version: 1.0
"""
import numpy as np
import cv2
import math
from scipy.ndimage.interpolation import rotate

# Moves mask in certain position and returns it as int (1 = foreground, 0 = background)
def moveMask(mask, block_size, transformStep, axis, value=0):
    # roll image in direction
    blockStep = block_size*transformStep
    rolled_mask = np.roll(mask.astype(int), blockStep, axis)

    # zero edges
    height, width = mask.shape
    if axis == 0:
        zeros = np.zeros((abs(blockStep), width))
        ones =  np.ones((height-abs(blockStep), width))
        if transformStep > 0:
            edge_mask = np.vstack([zeros,ones])
        else:
            edge_mask = np.vstack([ones, zeros])
    else:
        zeros = np.zeros((height, abs(blockStep)))
        ones =  np.ones((height, width-abs(blockStep)))
        if transformStep > 0:
            edge_mask = np.hstack([zeros,ones])
        else:
            edge_mask = np.hstack([ones, zeros])
    
    rolled_mask = rolled_mask*edge_mask

    # add to edges value if needed 
    if value != 0:
        edge_mask = np.where(edge_mask==0, 255, 0)
        rolled_mask = rolled_mask+edge_mask
    return rolled_mask

# gets fingerprint object and returns rotated img, mask and smoothedorientationfield
def rotateMask(mask, angle):
    if angle == 0: return mask
    #create copy of eveything
    degmask = np.copy(mask)
    #compute
    degmask = rotate(degmask, angle=angle, cval=0)
    return degmask

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
def alighn_masks(mask_1, mask_2, block_size, step_size=2, minvr=0.3, angle_step=15):
    angle_range = 45
    mask_height, mask_width = mask_1.shape
    # get all possible rotations of seond fingerprint
    print('Aligning process: ', flush=False)
    allRotations = []
    perc = 0
    for angle in range(-angle_range, angle_range, angle_step):    #30, 360, 30
        rotated_mask = rotateMask(mask_2, angle)
        allRotations.append(rotated_mask)
        # perc to print
        perc += angle_step
        print('Masks: ', int(perc/(angle_range*2)*100), "%", end="\r", flush=True)
    print(flush=False)
    # alighn all possible
    # (-half; half)
    steps_width = int((mask_width/5)/(block_size))
    steps_height = int((mask_height/5)/(block_size))

    max_s = 0
    max_pos = (0,0)
    max_angle = 0
    actual_angle = -angle_range

    iteration = 0
    for rotation in allRotations:
        #upshape
        rotation = upshape(rotation, mask_1.shape)

        for y in range(-steps_height, steps_width, step_size):
            for x in range(-steps_width, steps_width,step_size):
                # move orientation field
                moved_mask = moveMask(rotation, block_size, x, 0)
                moved_mask = np.array(moveMask(moved_mask, block_size, y, 1))
                
                # downshape
                moved_mask = downshape(moved_mask,mask_1.shape)

                # check min alighment rule
                multiplied = mask_1 * moved_mask
                multiplied_non_zero = np.count_nonzero(multiplied)
                if max_s < multiplied_non_zero:
                    max_s = multiplied_non_zero
                    max_angle = actual_angle
                    max_pos = (x, y)  
                    
        print('Aligning masks: ',int((iteration)/(len(allRotations)-1)*100), "%", end="\r", flush=True)
        actual_angle += angle_step 
        iteration+=1
        
    print(flush=False)
    print("Best alighnment S value is: ", "{:.2f}".format(max_s/(mask_height*mask_width)*100), "% for angle: ", max_angle, "° and moved position by: ", max_pos)

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