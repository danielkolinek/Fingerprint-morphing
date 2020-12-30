"""
   	Project Practice PP1 2019/2020 << Morphing of Fingerprints >>
    File:   morph.py
    Author: Daniel Kolinek
    Date:   05/2020
    Brief:  Implements morphing of two fingerprints
    Version: 1.0
"""
import sys
import cv2
import numpy as np
from PIL import Image
import scipy
# matplotlib
import matplotlib.pyplot as plt

# my files
from functions.coreDetection import detectCore
from functions.alighnOrientFields import alighn, rotateEverything, moveFingerprint, upshape, downshape, cutIntersections
from objects.fingerprint import Fingerprint
from functions.localRingeFrequencies import localRidgeFreq
from functions.minutiae import minutiae
from functions.cutline import getCutline
from functions.imageBasedMorphing import imageBasedMorphing
from functions.args import parse_args
from objects.PlotRes import PlotRes

def saveImageTiffDPI(image, filename, dpi=500):
    filename += '.tif' 
    """cv2.imshow("OKOK", image)
    #debug shows with cv2
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    """
    #cv2.imwrite(filename, image)
    #im = Image.open(filename)
    im = Image.fromarray(np.uint8(image), 'L')
    im.save(filename, dpi=(dpi, dpi))


def morphing(args, fingerprint_1_image, fingerprint_2_image):
    #init ploting obj
    plot_res = PlotRes()

    #Get blocksize
    block_size = int(args.blocksize)

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
    plot_res.fingerprint_1_start = np.copy(fingerprint_1.fingerprint)
    plot_res.fingerprint_2_start = np.copy(fingerprint_2.fingerprint)

    # get orientation field visible for humans
    plot_res.orientation_field_1 = fingerprint_1.drawOrientationField(fingerprint_1.smooth_orientation_field, fingerprint_1.block_size)
    plot_res.orientation_field_2 = fingerprint_2.drawOrientationField(fingerprint_2.smooth_orientation_field, fingerprint_2.block_size)

    # get aligment
    max_pos, max_angle = alighn(fingerprint_1, fingerprint_2, 1)

    # move fingerprint 2 from alignment results
    fingerprint_2.moveEverything(max_pos, max_angle, fingerprint_1.fingerprint.shape) #recalc_ori_2 = fingerprint_2.moveEverything(max_pos, max_angle, fingerprint_1.fingerprint.shape)

    # show alignment of orientation fields
    plot_res.alignment_draw = fingerprint_1.drawOrientationField(fingerprint_2.smooth_orientation_field,block_size, plot_res.fingerprint_1_start, True, (255,0,0))
    # get only intersecting parts
    cutIntersections(fingerprint_1, fingerprint_2)
    #cv2.imshow("sm_or_field_1", fingerprint_1.drawOrientationField(fingerprint_1.smooth_orientation_field,fingerprint_1.block_size))
    #cv2.imshow("sm_or_field_2", fingerprint_2.drawOrientationField(fingerprint_2.smooth_orientation_field,fingerprint_2.block_size))

    # get intersections for drawing
    plot_res.intersection_gray_1 = fingerprint_1.fingerprint
    plot_res.intersection_gray_2 = fingerprint_2.fingerprint

    # get local ringe frequencies
    print("Local Ringe Frequency 1")
    plot_res.freq_1 = freq_1 = localRidgeFreq(fingerprint_1)
    print("Local Ringe Frequency 2")
    plot_res.freq_2 = freq_2 = localRidgeFreq(fingerprint_2)

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

    #save result
    try: 
        cv2.imwrite(args.save+".jpg", morph_res)
    except: 
        None
    
    if(args.plot):
        #plot results
        plot_res.fingerprint_1_end = fingerprint_1.fingerprint   
        plot_res.fingerprint_2_end = fingerprint_2.fingerprint    
        plot_res.drawRes(minutiae_1, minutiae_2, barycenter, cutline, morph_res)

    return morph_res

    
if __name__ == "__main__":

    #load args from bashline
    parser = parse_args()
    args = parser.parse_args()

    fingerprint_1_image = None
    fingerprint_2_image = None


    #Try to load images of fingerprints
    if args.image_1 is not None and args.image_2 is not None:
        fingerprint_1_image = cv2.imread(args.image_1)
        fingerprint_2_image = cv2.imread(args.image_2)
        morph_res = morphing(args, fingerprint_1_image, fingerprint_2_image)
        if args.save is not None:
            saveImageTiffDPI(morph_res, args.save)
    elif args.tests is not None :
        print("tests")
    else:
        parser.print_help()
        exit(42)