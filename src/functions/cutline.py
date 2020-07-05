"""
   	Project Practice PP1 2019/2020 << Morphing of Fingerprints >>
    File:   cutline.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements cutline estimation

    Code inspired by paper: On the Feasibility of Creating Double-Identity Fingerprints
    [Online at: https://www.researchgate.net/publication/311622605_On_the_Feasibility_of_Creating_Double-Identity_Fingerprints].
    Version: 1.2
"""

import math
import numpy as np
import sys
import cv2

# a_l = line[0], b_l = line[1], c_l = line[2]
def countdDistL(line, x, y):
    a_l, b_l, c_l = line
    return abs(a_l*x + b_l*y + c_l)/math.sqrt(a_l**2 + b_l**2)

def countC_mask(fingerprint, d_max, beta, barycenter):
    # the line l passing through p with angle beta
    a_l = math.sin(beta)
    b_l = math.cos(beta)
    c_l = -barycenter[0]*a_l -barycenter[1]*b_l

    height, width = fingerprint.fingerprint.shape
    half_block_size = fingerprint.block_size // 2

    C_mask = np.zeros((fingerprint.fingerprint.shape))
    for j in range(half_block_size, height, fingerprint.block_size):
        for i in range(half_block_size, width, fingerprint.block_size):
            dist_l = countdDistL((a_l, b_l, c_l), i, j)
            if(fingerprint.smooth_orientation_field[j][i] != 0 and d_max >= dist_l):
                C_mask[j][i] = 1
    return C_mask, a_l, b_l, c_l

# counts Z for zeta in 12 equalization of paper
def countZ(v, u, t):
    return 1/1+math.exp(-t*(v-u))

# returns tuple : (count of points bellow, ount of points above)
def countPointsAboveBellow(line, points):
    a_l, b_l, c_l = line
    bellow_count = 0
    above_count = len(points)
    for point in points:
        # get if bellow
        line_sum = a_l*point[0] + b_l*point[1] + c_l
        if ((line_sum < 0) and b_l > 0) or ((line_sum > 0) and b_l < 0): 
            bellow_count += 1
            above_count -= 1
    return (bellow_count, above_count)

# gets y for given x on given line
# a_l = line[0], b_l = line[1], c_l = line[2]
def getY(line, x):
    a_l, b_l, c_l = line
    return (-a_l*x-c_l)/b_l

def getX(line, y):
    a_l, b_l, c_l = line
    return (-b_l*y-c_l)/a_l

def drawCutline(line, img):
    start_x = -1000
    start_y = -1000
    if abs(int(getY(line, start_x))) > 42000: 
        start_x = int(getX(line, start_y))
    else:
        start_y =int(getY(line, start_x))
    end_x = 1000
    end_y = 1000
    if abs(int(getY(line, end_x))) > 42000: 
        end_x = int(getX(line, end_y))
    else:
        end_y =int(getY(line, end_x))
    #print((start_x, start_y), (end_x, end_y))
    return cv2.line(img, (start_x, start_y), (end_x, end_y), (0, 0, 255), 2) 


def getCutline(fingerprint_1, fingerprint_2, freq_1, freq_2, barycenter, minutiae_1, minutiae_2, d_max, angle_deg_step=30, w_o = 0.4, w_v = 0.2, w_m = 0.4):
    print("Counting cutline: 0%", end="\r", flush=True)
    #for now
    r1 = 1
    r2 = 2
    # go throught all angles and get max_S_c with angle beta
    max_S_c = - 42
    max_line = (0, 0, 0)
    max_angle = 0
    # get min_F and max_F
    min_F_1 = np.min(freq_1)
    min_F_2 = np.min(freq_2)
    min_F = min_F_1 if min_F_1 < min_F_2 else min_F_2
    max_F_1 = np.max(freq_1)
    max_F_2 = np.max(freq_2)
    max_F = max_F_1 if max_F_1 < max_F_2 else max_F_2
    
    for angle in range(0, 180+angle_deg_step, angle_deg_step):
        beta = math.radians(angle)
        # get C mask
        C_mask, a_l, b_l, c_l = countC_mask(fingerprint_1, d_max, beta, barycenter)
        C_mask_sum = np.sum(C_mask)

        #### get S_o
        S_o = np.sum(
                    np.where(
                        np.logical_and(fingerprint_1.smooth_orientation_field!=0, C_mask != 0), 
                        (r1+r2)*(1-(2*abs(fingerprint_1.smooth_orientation_field-fingerprint_2.smooth_orientation_field))/math.pi),
                        0)
                )/(r1*C_mask_sum+r2*C_mask_sum)
        
        #### get S_v
        S_v = np.sum(
                    np.where(
                        np.logical_and(fingerprint_1.smooth_orientation_field!=0, C_mask != 0), 
                        1-abs(freq_1 - freq_2)/(max_F-min_F),
                        0)
                )/C_mask_sum

        #### get S_M
        #get mu and tau
        mu_m = max(len(minutiae_1), len(minutiae_2))
        tau = 0
        # get zetas
        A_N_1, A_P_1 = countPointsAboveBellow((a_l, b_l, c_l), minutiae_1)
        A_N_2, A_P_2 = countPointsAboveBellow((a_l, b_l, c_l), minutiae_2)
        zeta_m_1 = (countZ(A_P_1, mu_m, tau) + countZ(A_N_2, mu_m, tau))/2
        zeta_m_2 = (countZ(A_P_2, mu_m, tau) + countZ(A_N_1, mu_m, tau))/2

        S_m = max(zeta_m_1, zeta_m_2)

        #### get S_c
        S_c = w_o*S_o + w_v*S_v + w_m*S_m

        # compare actual S_c with max S_c
        if S_c > max_S_c:
            max_S_c = S_c
            max_line = (a_l, b_l, c_l)
            max_angle = angle
        print("Counting cutline: ",int(angle/180*100),"%", end="\r", flush=True)

    print(flush=False)
    print("Cutline estimated under", max_angle, "° a=",max_line[0], "b=", max_line[1], "c=", max_line[2])
    return max_line


