import cv2
import math
import numpy as np


#function gets grayscale image and returns:
#   - orientation filed
#   - smoothed orientation field by GaussianBlur
#   - coherence matrix from (https://www.ijcaonline.org/allpdf/pxc387482.pdf page 3-4)
def getOrientationField(img, block_size):
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
            for u in range(i-half_block_size, i+half_block_size):
                for v in range(j-half_block_size, j+half_block_size):
                    sum_Vx += (grad_x[v][u]**2) - (grad_y[v][u]**2)
                    sum_Vy += 2*grad_x[v][u]*grad_y[v][u]
                    sum_for_coherence_1 += abs(sum_Vx-sum_Vy) 
                    sum_for_coherence_2 += sum_Vx-sum_Vy
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
            index_i = int((i-half_block_size)/block_size)
            index_j = int((j-half_block_size)/block_size)
            orientationMatSmooth[j][i] = math.atan2(low_pass_filter_phi_y[index_j][index_i], low_pass_filter_phi_x[index_j][index_i])*0.5
    return (orientationMat, orientationMatSmooth, coherence)

def drawOrientationField(img, orientation_field, block_size, im_name):
    half_block_size = int(block_size/2)
    backtorgb = cv2.cvtColor(img,cv2.COLOR_GRAY2RGB)
    #backtorgb = np.zeros(backtorgb.shape) #for black bg
    y, x = img.shape
    for i in range(half_block_size, x-half_block_size, block_size):
        for j in range(half_block_size, y-half_block_size, block_size):
            movex = int(math.cos(orientation_field[j][i])*half_block_size)
            movey = int(math.sin(orientation_field[j][i])*half_block_size)
            #just to draw result for people readable
            x0 = i - movex
            y0 = j - movey
            x1 = i + movex
            y1 = j + movey
            cv2.line(backtorgb, (x0, y0), (x1, y1), (0,0, 255), 1)
    cv2.imshow(im_name, backtorgb)
    return

def drawCoherence(img, coherence, block_size, im_name):
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
    return