# inspirated by https://github.com/mehmetaydar/fingerprint-alignment/blob/master/frequency.py

import numpy as np
import cv2
import math
from scipy.ndimage import rotate
import time

from PIL import Image, ImageDraw
from functools import reduce
from functools import cmp_to_key

def points_on_line(line, W):
    im = Image.new("L", (W, 3 * W), 100)
    draw = ImageDraw.Draw(im)
    draw.line([(0, line(0) + W), (W, line(W) + W)], fill=10)
    im_load = im.load()

    points = []
    for x in range(0, W):
        for y in range(0, 3 * W):
            if im_load[x, y] == 10:
               points.append((x, y - W))

    del draw
    del im

    dist = lambda x_y: (x_y[0] - W / 2) ** 2 + (x_y[1] - W / 2) ** 2

    return sorted(points, key=cmp_to_key( lambda x, y: dist(x) < dist(y)))[:W]

def vec_and_step(tang, W):
    (begin, end) = get_line_ends(0, 0, W, tang)
    (x_vec, y_vec) = (end[0] - begin[0], end[1] - begin[1])
    length = math.hypot(x_vec, y_vec)
    (x_norm, y_norm) = (x_vec / length, y_vec / length)
    step = length / W

    return (x_norm, y_norm, step)

def get_line_ends(i, j, W, tang):
    if -1 <= tang and tang <= 1:
        begin = (i, (-W/2) * tang + j + W/2)
        end = (i + W, (W/2) * tang + j + W/2)
    else:
        begin = (i + W/2 + W/(2 * tang), j + W/2)
        end = (i + W/2 - W/(2 * tang), j - W/2)
    return (begin, end)

def localRidgeFreq(fingerprint):
    print("Local Ringe Frequency")
    w = fingerprint.block_size            # has to be multiple of block_size

    block_size = fingerprint.block_size
    half_block_size = int(block_size/2)
    height, width = fingerprint.fingerprint.shape

    result = np.zeros(fingerprint.fingerprint.shape)

    for j in range(half_block_size, height-half_block_size, block_size):
        for i in range(half_block_size, width-half_block_size, block_size):
            if fingerprint.smooth_orientation_field[j][i] == 0.0 : continue #check if on fingerprint

            # get oriented vector for x-signature
            tang = math.tan(fingerprint.smooth_orientation_field[j][i])
            #print(fingerprint.smooth_orientation_field[j][i])
            ortho_tang = -1 / tang          
            (x_norm, y_norm, step) = vec_and_step(tang, block_size)
            (x_corner, y_corner) = (0 if x_norm >= 0 else block_size, 0 if y_norm >= 0 else block_size)          

            # get x-signature
            X = []
            #cv2.imshow("Freq", fingerprint.fingerprint)
            #cv2.waitKey(0)
            #cv2.destroyAllWindows()
            for k in range(0, block_size):
                line = lambda x: (x - x_norm * k * step - x_corner) * ortho_tang + y_norm * k * step + y_corner
                points = points_on_line(line, w)
                level = 0
                #print(points)
                for point in points:
                    level += fingerprint.fingerprint[int(point[1] + (j-half_block_size)/block_size)][int(point[0] + (i-half_block_size)/block_size)]
                    #print([int(point[1] + (j-half_block_size)/block_size)],[int(point[0] + (i-half_block_size)/block_size)])
                    #time.sleep(1)
                    if(fingerprint.fingerprint[int(point[1] + (j-half_block_size)/block_size)][int(point[0] + (i-half_block_size)/block_size)]!=255):
                        print([int(point[1] + (j-half_block_size)/block_size)],[int(point[0] + (i-half_block_size)/block_size)])
                        print(fingerprint.fingerprint[int(point[1] + (j-half_block_size)/block_size)][int(point[0] + (i-half_block_size)/block_size)])
                
                X.append(level)
            treshold = 100
            upward = False
            last_level = 0
            last_bottom = 0
            count = 0.0
            spaces = len(X)
            for level in X:
                if level < last_bottom:
                    last_bottom = level
                if upward and level < last_level:
                    upward = False
                    if last_bottom + treshold < last_level:
                        count += 1
                        last_bottom = last_level
                if level > last_level:
                    upward = True
                last_level = level
            #print(spaces)
            #time.sleep(10)
            result[j-half_block_size:j+half_block_size, i-half_block_size:i+half_block_size] = (count / spaces) if spaces > 0 else 0
            #print(count/spaces)
    cv2.imshow("Freq", result)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
            
    exit()
    return #array