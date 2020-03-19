import sys
import cv2
import numpy as np

import orientField

def getBlackWhite(img):
    #load image in grey
    gray= cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #normalize image
    cv2.normalize(gray, gray, 0, 255, cv2.NORM_MINMAX)
    #trashold image to black and white
    #_, blackWhite = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
    #crop redundant white background
    #blackWhite = cropBg(blackWhite)
    return gray

# Function gets black and white image
# returns image with croped redundant white background
def cropBg(img):
    leftx = 10000000
    rightx = 0
    downy = 10000000
    upy = 0 
    line = 0
    for x in img:
        for y in range(len(x)):
            if x[y] != 255:
                if line > upy:
                    upy = line
                if line < downy:
                    downy = line
                if y > rightx:
                    rightx = y
                if y < leftx:
                    leftx = y
        line+=1
    return img[downy:upy, leftx:rightx]

def main():
    #Check parametres
    if(len(sys.argv)!= 3):
        print("Bad arguments")
        exit(42)
    
    #Try to get black and white images 
    try:
        black_white_1 = getBlackWhite(cv2.imread(sys.argv[1]))
        #black_white_2 = getBlackWhite(cv2.imread(sys.argv[2]))
    except:
        print("Wrong file name")
        exit(42)
        
    block_size = 10
    orientation_field, orientation_field_smooth = orientField.getOrientationField(black_white_1, block_size)
    orientField.drawOrientationField(black_white_1, orientation_field, block_size, 'Orientation field')
    orientField.drawOrientationField(black_white_1, orientation_field_smooth, block_size, 'Orientation field smooth')
    #orientField.drawCoherence(black_white_1, coherence_mat, block_size, 'Coherence matrix')
    #cv2.imshow('Orientation field', orientation_field)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    
    # Models fine tuning procedure.
    main()