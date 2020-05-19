"""
   	Project Practice PP1 2019/2020 << Morphing of Fingerprints >>
    File:   morphingFunctions.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements functions needed for fingerprint morphing

    Code inspired by paper: On the Feasibility of Creating Double-Identity Fingerprints
    [Online at: https://www.researchgate.net/publication/311622605_On_the_Feasibility_of_Creating_Double-Identity_Fingerprints].
    Version: 1.0
"""

# morphing functions implemented like: https://www.researchgate.net/publication/311622605_On_the_Feasibility_of_Creating_Double-Identity_Fingerprints

import numpy as np
import cv2
from functions.cutline import countdDistL, countPointsAboveBellow, countZ

# a_l = line[0], b_l = line[1], c_l = line[2]
def countWlmaxXY(d_max, x, y, line):
    # count max part
    max_part = max(0, (d_max-countdDistL(line, x, y))/(2*d_max))
    # a_l = line[0], b_l = line[1], c_l = line[2]
    if line[0]*x + line[1]*y + line[2] >= 0: return 1 - max_part
    else: return max_part

def getPN(minutiae_1, minutiae_2, cutline, fingerprint_1, fingerprint_2):
    mu_m = max(len(minutiae_1), len(minutiae_2))
    tau = 0
    a_l, b_l, c_l = cutline
    A_N_1, A_P_1 = countPointsAboveBellow((a_l, b_l, c_l), minutiae_1)
    A_N_2, A_P_2 = countPointsAboveBellow((a_l, b_l, c_l), minutiae_2)
    zeta_m_1 = (countZ(A_P_1, mu_m, tau) + countZ(A_N_2, mu_m, tau))/2
    zeta_m_2 = (countZ(A_P_2, mu_m, tau) + countZ(A_N_1, mu_m, tau))/2

    if zeta_m_1 >= zeta_m_2: return fingerprint_1.fingerprint, fingerprint_2.fingerprint
    else: return fingerprint_2.fingerprint, fingerprint_1.fingerprint