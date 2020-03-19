import cv2
import math
import numpy as np

""" NOT WORKING
def normalization(img, M0, VAR0):
    norm_img = img.copy()
    row_range, col_range = img.shape
    M = np.mean(img)
    VAR = np.var(img)
    for x in range(row_range):
        for y in range(col_range):
            to_sqrt = (VAR0 * ((img[x][y] - M)**2))/VAR
            norm_sqrt = math.sqrt(to_sqrt)
            if img[x][y] > M:
                norm_img[x][y] = int(M0 + norm_sqrt)
            else:
                norm_img[x][y] = int(M0 - norm_sqrt)

    return norm_img
"""

def getOrientationField(img, blockSize):
    #1. normalize image
    orientationMat = np.zeros(img.shape)

    #for showing drawing reslt uncoment this and on the end
    backtorgb = cv2.cvtColor(img,cv2.COLOR_GRAY2RGB)
    backtorgb = np.zeros(backtorgb.shape)

    #2. gradients with sobel
    sobel_kernel = 3
    grad_x = cv2.Sobel(img,cv2.CV_8U,1,0,ksize=sobel_kernel)
    grad_y = cv2.Sobel(img,cv2.CV_8U,0,1,ksize=sobel_kernel)

    #3. local orientation of each block center at pixel (i,j)
    row_range, col_range = img.shape
    row_range = int(row_range - blockSize / 2)
    col_range = int(col_range - blockSize / 2)

    Vx = np.zeros(img.shape)
    Vy = np.zeros(img.shape)
    theta = np.zeros(img.shape)

    low_pass_x = np.zeros(img.shape)
    low_pass_y = np.zeros(img.shape)

    half_block_size = int(blockSize/2)
    for i in range(half_block_size, row_range - half_block_size, blockSize):
        for j in range(half_block_size, col_range - half_block_size, blockSize):
            sum_Vx = 0.0
            sum_Vy = 0.0
            for u in range(i - half_block_size, i+half_block_size):
                for v in range(j - half_block_size, j+half_block_size):
                    sum_Vy += 2*grad_x[u][v]*grad_y[u][v]
                    sum_Vx += (grad_x[u][v]**2) - (grad_y[u][v]**2)
            sum_theta = 0.0
            if(sum_Vx != 0 and sum_Vy != 0):
                sum_theta = 0.5 * math.atan(sum_Vy / sum_Vx)
            Vx[i][j] = sum_Vx
            Vy[i][j] = sum_Vy
            theta[i][j] = sum_theta

            #4. low pass filter
            V = math.sqrt(sum_Vx**2 + sum_Vy**2)
            low_pass_x[i][j] = V*math.cos((2*sum_theta)*math.pi/180)
            low_pass_y[i][j] = V*math.sin((2*sum_theta)*math.pi/180)

            sum_low_pass_x = 0
            sum_low_pass_y = 0
            filter_size = 5
            half_filter = int(filter_size/2)
            for u in range(-half_filter, half_filter):
                for v in range(-half_filter, half_filter):
                    sum_low_pass_x += int(img[u][v]) * low_pass_x[i-u*filter_size][j-v*filter_size]
                    sum_low_pass_y += int(img[u][v]) * low_pass_y[i-u*filter_size][j-v*filter_size]

            #5. Compute local ringe oreintation
            res = 0
            if sum_low_pass_x != 0 and sum_low_pass_y != 0:
                res = 0.5*math.atan(((sum_low_pass_y/sum_low_pass_x) * (180 / math.pi))) 
            
            orientationMat[i][j] = res
            
            #just to draw result for people readable
            x0 = i + half_block_size
            y0 = j + half_block_size
            x1 = int(half_block_size*math.cos(res-0.5*math.pi)+x0)
            y1 = int(half_block_size*math.sin(res-0.5*math.pi)+y0)
            cv2.line(backtorgb, (y0, x0), (y1, x1), (0,0, 255), 1)
            
            
    cv2.imshow('Orientation field', backtorgb)
    cv2.imshow('Normalized image', img)
    return orientationMat