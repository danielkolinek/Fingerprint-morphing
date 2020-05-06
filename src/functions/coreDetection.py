import numpy as np
import cv2
import math

#neighbourhood of orientations (starts at [-1, -1] an continues anticlockwise)

def angle_diff(angle1, angle2):
    #sub angles
    angle = angle1 - angle2
    #need to repair agngle just to range 0 - pi
    if abs(angle) > math.pi:
        epsilon = -1 if angle < 0 else 1
        angle = -1 * epsilon * (2*math.pi - abs(angle))
    return angle
                    
def getPointcare(fingerprint):       
    y, x = fingerprint.fingerprint.shape
    pointcare_img = cv2.cvtColor(fingerprint.fingerprint,cv2.COLOR_GRAY2RGB)
    #to copmpare all neighbours from neighbourhood in distance 1 (blocksize)
    barier = int(fingerprint.block_size*1.5)
    located_core = False
    located_delta = False
    
    max_diff = 0
    max_x_y = (barier, barier)
    delta_tolerance = 10*math.pi/180
    for j in range(barier, y-barier, fingerprint.block_size):
        for i in range(barier, x-barier, fingerprint.block_size):
            angles = getAnglesInNeighbourhood(i, j, fingerprint.orientation_field, fingerprint.block_size)
            #---core singular point find
            index = angleDiffForDelta(angles)
            if max_diff < index and fingerprint.mask[j][i] == 255:
                max_diff = index
                max_x_y = (i, j)
            """ older version
            if not located_core :
                if index == math.pi and fingerprint.mask[j][i] == 255:
                    cv2.circle(pointcare_img, (i, j), 2, (0,0,255), -1)
                    located_core = True
            """  
            #---delta singular point find
            index = angleDiffForDelta(angles)
            #if not located_delta:
            if index >= (-math.pi - delta_tolerance) and index <= (- math.pi+delta_tolerance) and fingerprint.mask[j][i] == 255:
                cv2.circle(pointcare_img, (i, j), 2, (0,255,0), -1)
                located_delta = True
              
    cv2.circle(pointcare_img, max_x_y, 2, (0,0,255), -1)
    print(max_x_y)
    return pointcare_img     

def angleDiffForCorePoint(angles):
    index = 0
    angles_tmp = angles.copy()
    #prepare array filled fith orientations in neighbourhood  
    for k in range(8):
        #normalization for angles 0-pi/2
        if abs(angle_diff(angles_tmp[k], angles_tmp[k+1])) > math.pi*0.5:
            index += angle_diff(angles_tmp[k], angles_tmp[k+1]+math.pi)
        else:
            index += angle_diff(angles_tmp[k], angles_tmp[k+1])
    return index

def angleDiffForDelta(angles):
    index = 0
    angles_tmp = angles.copy()
    #prepare array filled fith orientations in neighbourhood  
    for k in range(8):
        #normalization for angles 0-pi/2
        if abs(angle_diff(angles_tmp[k], angles_tmp[k+1])) > math.pi*0.5:
            angles_tmp[k+1] += math.pi
        index += angle_diff(angles_tmp[k], angles_tmp[k+1])
    return index

def getAnglesInNeighbourhood(i, j, orientation_field, block_size):
    neighbourhood_anticlockwise = [
    [-block_size, -block_size], [-block_size, 0], [-block_size, block_size],
    [0, block_size], [block_size, block_size], [block_size, 0],
    [block_size, -block_size], [0, -block_size], [-block_size, -block_size]
    ]
    return [orientation_field[j - l][i - k] % math.pi for k, l in neighbourhood_anticlockwise]

def detectCore(fingerprint):
    #cv2.imshow("mask", mask)
    pointcare_img = getPointcare(fingerprint)
    return pointcare_img
    