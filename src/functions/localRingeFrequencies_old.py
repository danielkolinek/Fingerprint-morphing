import numpy as np
import cv2
import math
from scipy.ndimage import rotate
import time
def localRidgeFreq(fingerprint):
    print("Local Ringe Frquency")
    w = fingerprint.block_size
    l = w * 2       # has to be multiple block_size
    half_w = w/2
    half_l = l/2

    half_w_int = round(w/2)
    half_l_int = round(l/2)

    block_size = fingerprint.block_size
    half_block_size = int(block_size/2)
    step = l + half_block_size
    height, width = fingerprint.fingerprint.shape

    
    Omega = np.zeros(fingerprint.fingerprint.shape)

    #testing var
    all_count = 0
    bad_all = 0

    for j in range(half_block_size, height-half_block_size, block_size):
        for i in range(half_block_size, width-half_block_size, block_size):
            if fingerprint.smooth_orientation_field[j][i] == 0.0 : continue #check if on fingerprint

            # compute x-signature
            X = []
            cos_theta = math.cos(theta)
            sin_theta = math.sin(theta)
            for k in range(l):
                sumG = 0
                for d in range(w):
                    # compute u and v
                    u = round(i + (d - half_w) * cos_theta + (k - half_l) * sin_theta)
                    v = round(j + (d - half_w) * sin_theta + (half_l - k) * cos_theta)
                    if u >= 0 and u < width and v >= 0 and v < height:
                        sumG += fingerprint.fingerprint[v][u]
                X.append(sumG/w)
            
            # get count of peaks
            last = - 100000
            peaks_count = 0
            for x in X:
                if x >= last: # still not or right on peak
                    last = x
                elif x < last: # peak in iteration before
                    last = x
                    peaks_count += 1
            
            # check if last is peak
            if X[-1] > X [-2] : 
                peaks_count += 1
            
            """ old version of get how many ... (was working probably better)
            low = True
            pixels_count = 0
            peaks_count = 0
            for x in X:
                if x > 125 and low:
                    low = False
                    peaks_count += 1
                elif x <= 125:
                    low = True
                    pixels_count +=1
            """
            # get average 
            average_pixels = 0
            #print(l)
            average_pixels = peaks_count / (l-peaks_count)
            
            # count freq omega
            tmp_freq = 0
            if average_pixels != 0:
                tmp_freq = 1 / average_pixels

            Omega[j][i] = tmp_freq if tmp_freq <= 1/2 and tmp_freq >=1/25 else -1

            all_count+=1
            if Omega[j][i] == -1:
                bad_all+=1
                
                #cv2.imshow("oriented_window", oriented_window)
                #cv2.waitKey(0)
                #cv2.destroyAllWindows()
            #if Omega[j][i] == -1: print(tmp_freq)
            #return
    print(bad_all/all_count)
    return #array