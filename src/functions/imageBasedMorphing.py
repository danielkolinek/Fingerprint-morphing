import numpy as np
import cv2
from functions.morphingFunctions import countWlmaxXY, getPN

def imageBasedMorphing(d_max, cutline, fingerprint_1, fingerprint_2, minutiae_1, minutiae_2):
    morph_res = np.ones(fingerprint_1.fingerprint.shape)*255
    height, width = fingerprint_1.fingerprint.shape
    
    F_P, F_N = getPN(minutiae_1, minutiae_2, cutline, fingerprint_1, fingerprint_2) 
    
    for y in range(height):
        for x in range(width):
            if fingerprint_1.mask[y][x] == 0: continue

            wlmaxXY = countWlmaxXY(d_max, x, y, cutline)

            morph_res[y][x] = wlmaxXY*F_P[y][x] + (1 - wlmaxXY)*F_N[y][x]

    return morph_res