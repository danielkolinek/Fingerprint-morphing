"""
   	Project Practice PP1 2019/2020 << Morphing of Fingerprints >>
    File:   morph.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements morphing of two fingerprints
    Version: 1.0
"""
import argparse
import sys
import cv2
import numpy as np
# matplotlib
import matplotlib.pyplot as plt

# my files
from functions.coreDetection import detectCore, drawDetectedCore
from functions.alighnOrientFields import alighn, rotateEverything, moveFingerprint, upshape, downshape, cutIntersections
from objects.fingerprint import Fingerprint
from functions.localRingeFrequencies import localRidgeFreq
from functions.minutiae import minutiae, drawMinutiae
from functions.cutline import getCutline, drawCutline
from functions.imageBasedMorphing import imageBasedMorphing

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description='Morph two fingeprints')
    parser.add_argument("--image_1",
                        metavar="/path/to/first/fingerprint/image/", required=True,
                        help="Path to first fingerprint image")
    parser.add_argument("--image_2",
                        metavar="/path/to/second/fingerprint/image/", required=True,
                        help="Path to second fingerprint image")
    parser.add_argument('--blocksize', required=True,
                        metavar="Blocksize for orientation field",
                        help="Blocksize for orientation field (image will be divided into blocksize x blocksize squares\
                        and for each square will be counted orientation)")
    args = parser.parse_args()
    
    #Get blocksize
    block_size = int(args.blocksize)

    #Try to load images of fingerprints
    try:
        fingerprint_1_image = cv2.imread(args.image_1)
        fingerprint_2_image = cv2.imread(args.image_2)
    except:
        print("Wrong file name")
        exit(42)

    # initialize fingerprints
    print("Fingerprint_1 preparation")
    fingerprint_1 = Fingerprint(fingerprint_1_image, block_size)
    print("Fingerprint_2 preparation")
    fingerprint_2 = Fingerprint(fingerprint_2_image, block_size)
    
    # sort fingerprints based on their size of orientationfields
    if fingerprint_1.non_zero_orientation_field_count < fingerprint_2.non_zero_orientation_field_count:
        fingerprint_3 = fingerprint_1
        fingerprint_1 = fingerprint_2
        fingerprint_2 = fingerprint_3

    # detect most changes in fingerprint
    barycenter = detectCore(fingerprint_1)

    # make copy for show in plotlib
    fingerprint_1_draw = np.copy(fingerprint_1.fingerprint)
    fingerprint_2_draw = np.copy(fingerprint_2.fingerprint)

    # get orientation field visible for humans
    orientation_field_draw_1 = fingerprint_1.drawOrientationField(fingerprint_1.smooth_orientation_field, fingerprint_1.block_size)
    orientation_field_draw_2 = fingerprint_2.drawOrientationField(fingerprint_2.smooth_orientation_field, fingerprint_2.block_size)

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
    print("Local Ringe Frequency 1")
    freq_1 = localRidgeFreq(fingerprint_1)
    print("Local Ringe Frequency 2")
    freq_2 = localRidgeFreq(fingerprint_2)

    # get minutiae
    minutiae_1 = minutiae(fingerprint_1)
    minutiae_2 = minutiae(fingerprint_2)

    # get cutline
    #controll if fingerprint1 core is still on foreground
    if fingerprint_1.mask[barycenter[1]][barycenter[0]] == 0:
        # if not, then let it be middle of fingerprint
        print("Position of barycenter of the intersection region recalculation")
        barycenter = fingerprint_1.middle_pos()
        
        print(barycenter)

    d_max = 30
    cutline = getCutline(fingerprint_1, fingerprint_2, freq_1, freq_2, barycenter, minutiae_1, minutiae_2, d_max)
    morph_res = imageBasedMorphing(d_max, cutline, fingerprint_1, fingerprint_2, minutiae_1, minutiae_2)



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
    fig_1.set_figheight(15)
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
    
    # plot miniatues
    minutiae_1_draw = fig_1.add_subplot(3,3,3)
    minutiae_1_draw.imshow(drawMinutiae(intersection_gray_1, minutiae_1), cmap='gray')

    minutiae_2_draw = fig_1.add_subplot(3,3,6)
    minutiae_2_draw.imshow(drawMinutiae(intersection_gray_2, minutiae_2), cmap='gray')

    # plot cutline on fingerprint 1 and 2
    cutline_img = drawDetectedCore(fingerprint_1.fingerprint, barycenter) # .astype('uint8')
    cutline_img = drawCutline(cutline, cutline_img)
    cutline_draw = fig_1.add_subplot(3,3,7)
    cutline_draw.imshow(cutline_img, cmap='gray')

    cutline_img = drawDetectedCore(fingerprint_2.fingerprint, barycenter) # .astype('uint8')
    cutline_img = drawCutline(cutline, cutline_img)
    cutline_draw = fig_1.add_subplot(3,3,8)
    cutline_draw.imshow(cutline_img, cmap='gray')

    # plot morph
    morph_draw = fig_1.add_subplot(3,3,9)
    morph_draw.imshow(morph_res, cmap='gray')

    #show plots
    plt.show()
    #debug shows with cv2
    cv2.waitKey(0)
    cv2.destroyAllWindows()