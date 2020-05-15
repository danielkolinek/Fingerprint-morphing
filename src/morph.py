import sys
import cv2
import numpy as np
# matplotlib
import matplotlib.pyplot as plt

# my files
from functions.coreDetection import detectCore
from functions.alighnOrientFields import alighn, rotateEverything, moveFingerprint, upshape, downshape, cutIntersections
from objects.fingerprint import Fingerprint
from functions.localRingeFrequencies import localRidgeFreq

def main():
    #Check parametres
    if(len(sys.argv)!= 4):
        print("Bad arguments")
        exit(42)
    
    #Get blocksize
    block_size = int(sys.argv[3])

    #Try to load images of fingerprints
    try:
        fingerprint_1_image = cv2.imread(sys.argv[1])
        fingerprint_2_image = cv2.imread(sys.argv[2])
    except:
        print("Wrong file name")
        exit(42)

    # initialize fingerprints
    fingerprint_1 = Fingerprint(fingerprint_1_image, block_size)
    fingerprint_2 = Fingerprint(fingerprint_2_image, block_size)

    # make copy for show in plotlib
    fingerprint_1_draw = np.copy(fingerprint_1.fingerprint)
    fingerprint_2_draw = np.copy(fingerprint_2.fingerprint)

    # sort fingerprints based on their size of orientationfields
    if fingerprint_1.non_zero_orientation_field_count < fingerprint_2.non_zero_orientation_field_count:
        fingerprint_3 = fingerprint_1
        fingerprint_1 = fingerprint_2
        fingerprint_2 = fingerprint_3

    # get orientation field visible for humans
    orientation_field_draw_1 = fingerprint_1.drawOrientationField(fingerprint_1.smooth_orientation_field, fingerprint_1.block_size)
    orientation_field_draw_2 = fingerprint_2.drawOrientationField(fingerprint_2.smooth_orientation_field, fingerprint_2.block_size)

    #core point find
    #core = detectCore(fingerprint_1)
    #cv2.imshow("Detected core", core)

    # get aligment
    max_pos, max_angle = alighn(fingerprint_1, fingerprint_2, 1)

    # move fingerprint 2 from alignment results
    fingerprint_2.moveEverything(max_pos, max_angle, fingerprint_1.fingerprint.shape)

    # show alignment of orientation fields
    alignment_draw = fingerprint_1.drawOrientationField(fingerprint_2.smooth_orientation_field,block_size, orientation_field_draw_1, True, (255,0,0))

    # get only intersecting parts
    cutIntersections(fingerprint_1, fingerprint_2)
    #cv2.imshow("sm_or_field_1", fingerprint_1.drawOrientationField(fingerprint_1.smooth_orientation_field,fingerprint_1.block_size))
    #cv2.imshow("sm_or_field_2", fingerprint_2.drawOrientationField(fingerprint_2.smooth_orientation_field,fingerprint_2.block_size))

    # get intersections for drawing
    intersection_gray_1 = fingerprint_1.fingerprint
    intersection_gray_2 = fingerprint_2.fingerprint

    # get local ringe frequencies
    freq_1 = localRidgeFreq(fingerprint_1)
    freq_2 = localRidgeFreq(fingerprint_2)

    ##### plot results #####

    ## plot alighning part

    fig = plt.figure()
    fig.canvas.set_window_title('Results of aligning')
    # grayscale fingerprints
    fig.set_figheight(15)
    gray1 = fig.add_subplot(3,2,1)
    gray1.imshow(fingerprint_1_draw, cmap='gray')

    gray2 = fig.add_subplot(3,2,2)
    gray2.imshow(fingerprint_2_draw, cmap='gray')

    #orientation fields
    or1 = fig.add_subplot(3,2,3)
    or1.imshow(orientation_field_draw_1, cmap='gray')
    or2 = fig.add_subplot(3,2,4)
    or2.imshow(orientation_field_draw_2, cmap='gray')
    
    # alignment
    ali = fig.add_subplot(3,2,5)
    ali.imshow(alignment_draw, cmap='gray')

    

    ## plot optimal cutline part
    fig_1 = plt.figure()
    fig_1.canvas.set_window_title('Results of cutline')

    # intersecting fingerprints
    gray1_1 = fig_1.add_subplot(3,3,1)
    gray1_1.imshow(intersection_gray_1, cmap='gray')

    gray2_2 = fig_1.add_subplot(3,3,4)
    gray2_2.imshow(intersection_gray_2, cmap='gray')

    # ridge frequency
    freq_1_draw = fig_1.add_subplot(3,3,2)
    freq_1_draw.imshow(freq_1*255, cmap='gray')

    freq_2_draw = fig_1.add_subplot(3,3,5)
    freq_2_draw.imshow(freq_2*255, cmap='gray')

    #
    #tmp1 = fig.add_subplot(3,2,5)
    #tmp1.imshow(ori30, cmap='gray')

    #mask = fig.add_subplot(3,2,6)
    #mask.imshow(mask30, cmap='gray')

    #show plots
    plt.show()
    #debug shows with cv2
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__":
    
    # Models fine tuning procedure.
    main()