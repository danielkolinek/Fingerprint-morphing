"""
   	Morphing of Fingerprints
    File:   imageBasedMorphing.py
    Author: Daniel Kolinek
    Date:   05/2021
    Brief:  Implements fingerprint morphing base on minutiae

    Code inspired by paper: On the Feasibility of Creating Double-Identity Fingerprints
    [Online at: https://www.researchgate.net/publication/311622605_On_the_Feasibility_of_Creating_Double-Identity_Fingerprints].
    Version: 1.0
"""

import numpy as np
import cv2
from functions.morphingFunctions import countWlmaxXY, getPN

"""
    generate new fingerprint based on minutiae
"""
def minutiaeBasedMorphing(d_max, cutline, fingerprint_1, fingerprint_2, minutiae_1, minutiae_2, freq_1, freq_2):
    F_P = getPN(minutiae_1, minutiae_2, cutline, fingerprint_1, fingerprint_2) 
    morph_ori = morph_ori_freq(d_max, cutline, fingerprint_1.smooth_orientation_field, fingerprint_2.smooth_orientation_field, minutiae_1, minutiae_2, F_P)
    morph_freq = morph_ori_freq(d_max, cutline, freq_1, freq_2, minutiae_1, minutiae_2, F_P)
    morph_minutiae = morph_minutiae_fun(minutiae_1, minutiae_2, cutline)

    #save data for later use (for developing purpose) 
    """
    width = morph_minutiae.shape
    for x in range(width):
        print(morph_minutiae[x])
    """
    #easy save as numpy
    np.savetxt('morph_input_gen/morph_ori.csv',morph_ori, delimiter=',')
    np.savetxt('morph_input_gen/morph_freq.csv', morph_freq, delimiter=',')
    #save list of tupples as 
    with open('morph_input_gen/morph_minutiae.csv', 'w') as fp:
        fp.write('\n'.join('{},{}'.format(x[0],x[1]) for x in morph_minutiae))

    return morph_freq

"""
    function for morphing orientation field or frequency characteristic of ridges
        field_1 = orientation field / frequency characteristics from fingerprint above cutline
        field_2 = orientation field / frequency characteristics from fingerprint under cutline
"""
def morph_ori_freq(d_max, cutline, field_1, field_2, minutiae_1, minutiae_2, F_P):
    morph_res = np.zeros(field_1.shape)
    height, width = field_1.shape

    if F_P != 1:
        field_tmp = field_1
        field_1 = field_2
        field_2 = field_tmp

    for y in range(height):
        for x in range(width):
            wlmaxXY = countWlmaxXY(d_max, x, y, cutline)
            morph_res[y][x] = wlmaxXY*field_1[y][x] + (1 - wlmaxXY)*field_2[y][x]

    return morph_res

def morph_minutiae_fun(minutiae_1, minutiae_2, cutline):
    morph_minutiae = getPointsAboveBellow(cutline, minutiae_1)[1]+getPointsAboveBellow(cutline, minutiae_2)[0]
    return morph_minutiae

def getPointsAboveBellow(line, points):
    a_l, b_l, c_l = line
    bellow = []
    above = []
    for point in points:
        # get if bellow
        line_sum = a_l*point[0] + b_l*point[1] + c_l
        if ((line_sum < 0) and b_l > 0) or ((line_sum > 0) and b_l < 0): 
            bellow.append(point)
        else:
            above.append(point)
    return (bellow, above)