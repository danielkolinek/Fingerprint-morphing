"""
   	Project Practice PP1 2019/2020 << Morphing of Fingerprints >>
    File:   coreDetection.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements fingerprint basic core/delta detection by Pointcare image

    Code inspired by paper: Singular Point Detection for Efﬁcient Fingerprint Classiﬁcation
    [Online at: https://www.researchgate.net/publication/230771380_Singular_Point_Detection_for_Efficient_Fingerprint_Classification].
    Version: 1.2
"""

# pointcare from https://www.researchgate.net/publication/230771380_Singular_Point_Detection_for_Efficient_Fingerprint_Classification

import numpy as np
import cv2
import math

def getAnglesInNeighbourhood(i, j, orientation_field, block_size):
    """
    [block_size, 0], [block_size, -block_size], [0, -block_size], 
    [-block_size, -block_size], [-block_size, 0], [-block_size, block_size], 
    [0, block_size], [block_size, block_size], [block_size, 0]
    """
    neighbourhood_anticlockwise = [
        [0, block_size], [block_size, block_size], [block_size, 0],
        [block_size, -block_size], [0, -block_size], [-block_size, -block_size],
        [-block_size, 0], [-block_size,block_size], [0, block_size]
    ]
    res = []
    for neighbour in neighbourhood_anticlockwise:
        if orientation_field[j+neighbour[1]][i+neighbour[0]] == 0: return [] # do not count with edges
        res.append(orientation_field[j+neighbour[1]][i+neighbour[0]])
    return res

# pointcare value at specific position
def countPC(angles):
    pi_half = math.pi/2
    Bc = 0
    for x in range(len(angles)-1):
        pc = (angles[x+1]-angles[x])
        # Bc rule
        if abs(pc) < pi_half: Bc += pc
        elif pc <= -pi_half: Bc += math.pi + pc
        else: Bc += math.pi - pc
    return (1/(2*math.pi)) * Bc  
                    
def getPointcare(fingerprint):       
    y, x = fingerprint.fingerprint.shape
    #pointcare_img = cv2.cvtColor(fingerprint.fingerprint,cv2.COLOR_GRAY2RGB)
    #to copmpare all neighbours from neighbourhood in distance 1 (blocksize)
    barier = int(fingerprint.block_size*1.5)
    located_core = False
    located_delta = False
    max_PC = -42
    max_X_Y = (0,0)
    for j in range(barier, y-barier, fingerprint.block_size):
        for i in range(barier, x-barier, fingerprint.block_size):
            if fingerprint.smooth_orientation_field[j][i] == 0: continue
            #print(fingerprint.smooth_orientation_field[j][i])
            angles = getAnglesInNeighbourhood(i, j, fingerprint.smooth_orientation_field, fingerprint.block_size)
            if len(angles) < 2: continue
            #---core singular point find
            PC = countPC(angles)
            """
            if PC >= -1 and PC <= -0.5: cv2.circle(pointcare_img, (i,j), 2, (0,0,255), -1)
            elif PC >= 0.5 and PC <= 1: cv2.circle(pointcare_img, (i,j), 2, (0,255,0), -1)
            else: print(PC)
            """
            # pointcare (just get max) - gets maximum of changings in neighbourhood
            if(max_PC < PC):
                max_PC = PC
                max_X_Y = (i,j)

    return max_X_Y     

def detectCore(fingerprint):
    #cv2.imshow("mask", mask)
    max_X_Y = getPointcare(fingerprint)
    #exit()
    return max_X_Y

def drawDetectedCore(img, position):
    draw = cv2.cvtColor(img,cv2.COLOR_GRAY2RGB)
    cv2.circle(draw, position, 5, (255,0,0), -1)
    return draw
