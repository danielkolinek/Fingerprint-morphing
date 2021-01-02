"""
    Morphing of Fingerprints
    File:   minutiae.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements estimation of minutiae points

    Used lib from: https://github.com/tudoriliuta/FingerMatch/tree/master/src/libs
    Version: 1.2
"""

import numpy as np
import cv2
import math

from libs.enhancing import enhance_image
from libs.minutiae import process_minutiae, plot_minutiae

# if gray, than convert image to RGB (be carefull with opencv)
def drawMinutiae(img, minutiaes, gray=True):
    result = np.copy(img)
    if gray:
        result = cv2.cvtColor(result,cv2.COLOR_GRAY2RGB)
    for minutiae in minutiaes:
        result = cv2.circle(result, (minutiae[1], minutiae[0]), 5, (255,0,0), 2)
    return result

def minutiae(fingerprint):
    print("Processing thinned image")
    thinned = enhance_image(fingerprint.fingerprint)
    print("Processing minutiae")
    minutiaes = process_minutiae(thinned)    
    return minutiaes