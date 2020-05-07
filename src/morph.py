import sys
import cv2
import numpy as np
# matplotlib
import matplotlib.pyplot as plt

# my files
from functions.coreDetection import detectCore
from functions.alighnOrientFields import alighn
from objects.fingerprint import Fingerprint


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

    # get orientation field visible for humans
    orientation_field_draw_1 = fingerprint_1.drawOrientationField(fingerprint_1.fingerprint, fingerprint_1.smooth_orientation_field, fingerprint_1.block_size)
    orientation_field_draw_2 = fingerprint_2.drawOrientationField(fingerprint_2.fingerprint, fingerprint_2.smooth_orientation_field, fingerprint_2.block_size)

    #core point find
    #core = detectCore(fingerprint_1)
    #cv2.imshow("Detected core", core)

    alighn(fingerprint_1, fingerprint_2, 2)

    # plot results
    fig = plt.figure()
    # grayscale fingerprints
    fig.set_figheight(15)
    gray1 = fig.add_subplot(3,2,1)
    gray1.imshow(fingerprint_1.fingerprint, cmap='gray')
    fig.set_figheight(15)
    gray2 = fig.add_subplot(3,2,2)
    gray2.imshow(fingerprint_2.fingerprint, cmap='gray')

    #orientation fields
    or1 = fig.add_subplot(3,2,3)
    or1.imshow(orientation_field_draw_1, cmap='gray')
    or2 = fig.add_subplot(3,2,4)
    or2.imshow(orientation_field_draw_2, cmap='gray')
    
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