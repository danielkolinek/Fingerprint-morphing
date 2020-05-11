import cv2
import math
import numpy as np
from functions.alighnOrientFields import alighn, rotateEverything, moveFingerprint, upshape, downshape


class Fingerprint():
    def __init__(self, fingerprint, block_size):
        self.block_size = block_size
        self.fingerprint = self.addWhiteBorder(self.getGrayScaleNormalized(fingerprint),block_size)
        self.mask = self.getMask(self.fingerprint)
        self.orientation_field, self.smooth_orientation_field, self.coherence = self.getOrientationField(self.fingerprint, block_size, self.mask)
        self.non_zero_orientation_field_count = np.count_nonzero(self.smooth_orientation_field)

    # BG is black, fingerprint white
    def getMask(self, fingerprint):
        height, width = fingerprint.shape
        mask = np.zeros(fingerprint.shape)
        half_block_size = int(self.block_size/2)

        for y in range(height):
            start = 0
            end = 0
            detected_dark = False
            for x in range(0, width):
                if fingerprint[y][x] < 200:
                    if not detected_dark:
                        detected_dark = True
                        start = x
                    else:
                        end = x
            if detected_dark:
                for x in range(start, end):
                    mask[y][x] = 255
        return mask

    def getGrayScaleNormalized(self, img):
        #load image in grey
        gray= cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        #normalize image
        cv2.normalize(gray, gray, 0, 255, cv2.NORM_MINMAX)
        #crop redundant white background
        return self.cropBg(gray)

    def addWhiteBorder(self, gray, block_size):
        return cv2.copyMakeBorder(
                    gray,
                    top=block_size,
                    bottom=block_size,
                    left=block_size,
                    right=block_size,
                    borderType=cv2.BORDER_CONSTANT,
                    value=255
                )
    # Function gets black and white image
    # returns image with croped redundant white background
    def cropBg(self,gray):
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
        self.downy = downy
        self.upy = upy
        self.leftx = leftx
        self.rightx = rightx
        return gray[downy:upy, leftx:rightx]
        
    #function gets grayscale image and returns:
    #   - orientation filed
    #   - smoothed orientation field by GaussianBlur
    #   - coherence matrix from (https://www.ijcaonline.org/allpdf/pxc387482.pdf page 3-4)
    def getOrientationField(self, img, block_size, mask):
        #1. normalize image
        orientationMat = np.zeros(img.shape)

        #2. gradients with sobel
        sobel_kernel = 3
        grad_x = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=sobel_kernel)
        grad_y = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=sobel_kernel)

        #3. local orientation of each block center at pixel (i,j)
        y, x = img.shape

        #coherence matrix
        coherence =  np.zeros(img.shape)
        
        #variables for smoothing orientation field
        x_real = int(x/block_size)
        y_real = int(y/block_size)
        phi_x = np.zeros((y_real, x_real))
        phi_y = np.zeros((y_real, x_real))
        orientationMatSmooth = np.zeros(img.shape)

        #---orientation field
        half_block_size = int(block_size/2)
        for i in range(half_block_size, x-half_block_size, block_size):
            for j in range(half_block_size, y-half_block_size, block_size):
                # Orientation field
                sum_Vx = 0
                sum_Vy = 0
                sum_for_coherence_1 = 0
                sum_for_coherence_2 = 0

                # Compute only for fingerprint, not for background
                foreground = False

                for u in range(i-half_block_size, i+half_block_size):
                    for v in range(j-half_block_size, j+half_block_size):
                        sum_Vx += (grad_x[v][u]**2) - (grad_y[v][u]**2)
                        sum_Vy += 2*grad_x[v][u]*grad_y[v][u]
                        sum_for_coherence_1 += abs(sum_Vx-sum_Vy) 
                        sum_for_coherence_2 += sum_Vx-sum_Vy
                        if (mask[v][u] != 0):
                            foreground = True

                orientationMat[j][i] = 0
                sum_theta = 0
                if foreground: 
                    sum_theta = (math.pi + math.atan2(sum_Vy, sum_Vx))*0.5
                    orientationMat[j][i] = sum_theta
                    
                #filling phi's for smoothing orientation field
                index_i = int((i-half_block_size)/block_size)
                index_j = int((j-half_block_size)/block_size)
                phi_x[index_j][index_i] = math.cos(2*sum_theta)
                phi_y[index_j][index_i] = math.sin(2*sum_theta)

                coherence[j][i] = 0
                if(sum_for_coherence_1 > 0):
                    coherence[j][i] = abs(sum_for_coherence_2)/sum_for_coherence_1

        #---smoothing orientation field
        filter_size = 5
        low_pass_filter_phi_x = cv2.GaussianBlur(phi_x,(filter_size,filter_size), 1)
        low_pass_filter_phi_y = cv2.GaussianBlur(phi_y,(filter_size,filter_size), 1)
        for i in range(half_block_size, x-half_block_size, block_size):
            for j in range(half_block_size, y-half_block_size, block_size):
                orientationMatSmooth[j][i] =0
                if orientationMat[j][i] != 0:
                    index_i = int((i-half_block_size)/block_size)
                    index_j = int((j-half_block_size)/block_size)
                    orientationMatSmooth[j][i] = math.atan2(low_pass_filter_phi_y[index_j][index_i], low_pass_filter_phi_x[index_j][index_i])*0.5
                    
        return (orientationMat, orientationMatSmooth, coherence)

    # Function for drawing orientation field
    # to use picture as bg, just set backgroundImg = True and input img (img has to be in RGB)
    def drawOrientationField(self, orientation_field, block_size, img=None, backgroundImg=False, color=(0,0, 255)):
        half_block_size = int(block_size/2)
        result = cv2.cvtColor(np.ones(orientation_field.shape).astype('uint8')*255,cv2.COLOR_GRAY2RGB) if not backgroundImg else np.copy(img)
        #result = np.zeros(result.shape) #for black bg
        y, x = orientation_field.shape
        for i in range(half_block_size, x-half_block_size, block_size):
            for j in range(half_block_size, y-half_block_size, block_size):
                if orientation_field[j][i] != 0:
                    movex = int(math.cos(orientation_field[j][i])*half_block_size)
                    movey = int(math.sin(orientation_field[j][i])*half_block_size)
                    #just to draw result for people readable
                    x0 = i - movex
                    y0 = j - movey
                    x1 = i + movex
                    y1 = j + movey
                    cv2.line(result, (x0, y0), (x1, y1), color, 1)
        return result

    def drawCoherence(self, img, coherence, block_size, im_name):
        y, x = coherence.shape
        half_block_size = int(block_size/2)
        backtorgb = cv2.cvtColor(img,cv2.COLOR_GRAY2RGB)
        backtorgb.fill(255)
        for i in range(0, x, block_size):
            for j in range(0, y, block_size):
                if coherence[j][i] < 0.02:
                    color = (0, 255, 0) 
                elif coherence[j][i] < 0.03:
                    color = (255, 0, 0) 
                else:
                    color = (0, 0, 255) 
                cv2.rectangle(backtorgb, (i-half_block_size, j-half_block_size), (i+half_block_size, j+half_block_size), color, -1)
        cv2.imshow(im_name, backtorgb)

    def moveEverything(self, position, angle, shape):
        #rotate everything
        self.fingerprint, self.mask, self.orientation_field, self.smooth_orientation_field = rotateEverything(self, angle)
        #upsize part
        self.fingerprint = upshape(self.fingerprint, shape, 255).astype(np.uint8)
        self.mask = upshape(self.mask, shape).astype(np.uint8)
        self.orientation_field = upshape(self.orientation_field, shape)
        self.smooth_orientation_field = upshape(self.smooth_orientation_field, shape)
        #move everything
        self.fingerprint = moveFingerprint(self.fingerprint, self.block_size, position[0], 0, 255)
        self.fingerprint = np.array(moveFingerprint(self.fingerprint, self.block_size, position[1], 1, 255))   
        self.mask = moveFingerprint(self.mask, self.block_size, position[0], 0)
        self.mask = np.array(moveFingerprint(self.mask, self.block_size, position[1], 1))
        self.orientation_field = moveFingerprint(self.orientation_field, self.block_size, position[0], 0)
        self.orientation_field = np.array(moveFingerprint(self.orientation_field, self.block_size, position[1], 1))
        self.smooth_orientation_field = moveFingerprint(self.smooth_orientation_field, self.block_size, position[0], 0)
        self.smooth_orientation_field = np.array(moveFingerprint(self.smooth_orientation_field, self.block_size, position[1], 1))     
        #downsize part
        self.fingerprint = downshape(self.fingerprint, shape).astype(np.uint8)
        self.mask = downshape(self.mask, shape)
        self.orientation_field = downshape(self.orientation_field, shape)
        self.smooth_orientation_field = downshape(self.smooth_orientation_field, shape)
        """
        cv2.imshow("mask", self.mask)
        cv2.imshow("orientation_field", self.drawOrientationField(self.orientation_field, self.block_size))
        cv2.imshow("orientation_field_smooth", self.drawOrientationField(self.smooth_orientation_field, self.block_size))
        cv2.imshow("fingeprint", self.fingerprint)
        """