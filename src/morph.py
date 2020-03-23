import sys
import cv2
import numpy as np

import functions.orientField as orientField
import functions.coreDetection as coreDetection

def getGrayScaleNormalized(img):
    #load image in grey
    gray= cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #normalize image
    cv2.normalize(gray, gray, 0, 255, cv2.NORM_MINMAX)
    #crop redundant white background
    return cropBg(gray)

# Function gets black and white image
# returns image with croped redundant white background
def cropBg(gray):
    leftx = 10000000
    rightx = 0
    downy = 10000000
    upy = 0 
    line = 0
    ret,black_white = cv2.threshold(gray,100,255,cv2.THRESH_BINARY)
    for x in black_white:
        for y in range(len(x)):
            if x[y] != 255:
                if line > upy:
                    upy = line
                elif line < downy:
                    downy = line
                if y > rightx:
                    rightx = y
                elif y < leftx:
                    leftx = y
        line+=1
    return gray[downy:upy, leftx:rightx]

def addWhiteBorder(gray, block_size):
    return cv2.copyMakeBorder(
                gray,
                top=block_size,
                bottom=block_size,
                left=block_size,
                right=block_size,
                borderType=cv2.BORDER_CONSTANT,
                value=255
            )

def main():
    #Check parametres
    if(len(sys.argv)!= 4):
        print("Bad arguments")
        exit(42)
    
    #Try to get black and white images 
    try:
        gray_1 = getGrayScaleNormalized(cv2.imread(sys.argv[1]))
        #gray_2 = getGrayScaleNormalized(cv2.imread(sys.argv[2]))
    except:
        print("Wrong file name")
        exit(42)

    block_size = int(sys.argv[3])

    gray_1 = addWhiteBorder(gray_1, block_size)
    
    #orientation field
    orientation_field, orientation_field_smooth, coherence = orientField.getOrientationField(gray_1, block_size)
    #orientField.drawCoherence(gray_1, coherence, block_size, "Coherence")
    #orientField.drawOrientationField(gray_1, orientation_field, block_size, 'Orientation field')
    orientField.drawOrientationField(gray_1, orientation_field_smooth, block_size, 'Orientation field smooth')
    #core point find
    core = coreDetection.detectCore(gray_1, orientation_field_smooth, block_size)
    cv2.imshow("Detected core", core)
    #cv2.imshow('Orientation field', orientation_field)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    
    # Models fine tuning procedure.
    main()