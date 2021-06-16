import cv2
import numpy as np
import math


def gabor_filter(kernel_size, angle, freq):
    
    #half of  kernel size
    d = kernel_size // 2
    gabor = np.zeros((kernel_size, kernel_size), dtype=np.float32)

    # each value
    for r in range(kernel_size):
        for s in range(kernel_size):
            # distance from center
            ks = s - d
            kr = r - d

            # get kernel s
            _s = np.cos(angle) * ks + np.sin(angle) * kr

            # get kernel r
            _r = -np.sin(angle) * ks + np.cos(angle) * kr

            # fill kernel
            gabor[y, x] = np.exp(-(_x**2 + Gamma**2 * _y**2) / (2 * Sigma**2)) * np.cos(2*np.pi*_x/Lambda + Psi)

    return gabor

def getLocalOrientation(orientation, position, blocksize):
    half_blocksize = int(blocksize/2) if blocksize % 2 == 0 else int(blocksize/2-1)
    result = 0
    for y in range(position[0]-half_blocksize, position[0]+blocksize):
        for x in range(position[1]-half_blocksize, position[1]+half_blocksize):
            if orientation[y][x] != 0:
                result = orientation[y][x]
                break
        if result != 0:
            break
    return result

def rotate_image(image, angle):
  image_center = tuple(np.array(image.shape[1::-1]) / 2)
  rot_mat = cv2.getRotationMatrix2D(image_center, angle, 1.0)
  result = cv2.warpAffine(image, rot_mat, image.shape[1::-1], flags=cv2.INTER_LINEAR, borderValue=255)
  return result

def delete_too_close_minutiae(minutiaes, delta=70):
    for min1 in minutiaes:
        for min2 in minutiaes:
            if(((min2[1]-min1[1])**2 + (min2[0]-min1[0])**2)**0.5 < delta):
                minutiaes.remove(min2)

    return minutiaes

def insert_minutiae(morph_res, position, minutiae_mask, morph_ori, morph_freq):
    #load position of bifurcation
    posy, posx = position

    ## resize constat
    R = 6
    width = abs(int(
        minutiae_mask.shape[1] * 0.3
    ))
    height = abs(int(
        minutiae_mask.shape[0] * 0.3
    ))
    # print(minutiae_mask.shape[1] * 1/(2.54/500 * minutiae_mask.shape[1] *minutiae_mask.shape[0] *R), " ----- ", height)
    minutiae_mask = cv2.resize(minutiae_mask, (width, height))



    """
    ## resize by frequency
    width = abs(int(minutiae_mask.shape[1] * morph_freq[posy][posx] *0.8))
    width = width if width > 0 else int(minutiae_mask.shape[1] *0.8)
    height = abs(int(minutiae_mask.shape[0] * morph_freq[posy][posx] *0.8))
    height = height if height > 0 else int(minutiae_mask.shape[1] *0.8)
    minutiae_mask = cv2.resize(minutiae_mask, (width, height))
    """

    #get angle of turn and rotate mask
    phi = math.degrees(getLocalOrientation(morph_ori, (posy, posx), 10))
    minutiae_mask = rotate_image(minutiae_mask, phi)

    # multiply one mask on position
    mask_height, mask_width = minutiae_mask.shape
    half_mask_height = round(mask_height/2)
    half_mask_height = half_mask_height if mask_height % 2 == 0 else half_mask_height -1
    half_mask_width = round(mask_width/2)
    half_mask_width = half_mask_width if mask_width % 2 == 0 else half_mask_width -1
    xmask = 0
    ymask = 0
    for y in range(posy-half_mask_height, posy+half_mask_height):
        xmask = 0
        for x in range(posx-half_mask_width, posx+half_mask_width):
            if(y < morph_res.shape[0] and x < morph_res.shape[1]):
                morph_res[y][x] *= minutiae_mask[ymask][xmask]
            xmask+=1
        ymask+=1
    return morph_res

if __name__ == "__main__":
    # load needed arrays
    # numpy part
    morph_ori = np.loadtxt('morph_ori.csv', delimiter=',')
    morph_freq = np.loadtxt('morph_freq.csv', delimiter=',')

    # list of touples part 
    ## termintions
    import csv
    with open('morph_terminations.csv') as f:
        morph_terminations_string =[tuple(line) for line in csv.reader(f)]
    # covert list of strings (morph_minutiae) to list of ints
    morph_terminations=[]
    for x in morph_terminations_string:
        morph_terminations.append((int(x[0]), int(x[1])))

    ## bifurcations
    import csv
    with open('morph_bifurcations.csv') as f:
        morph_bifurcations_string =[tuple(line) for line in csv.reader(f)]
    # covert list of strings (morph_minutiae) to list of ints
    morph_bifurcations=[]
    for x in morph_bifurcations_string:
        morph_bifurcations.append((int(x[0]), int(x[1])))

    # create new blank space
    morph_res = np.ones(morph_ori.shape)*255

    #load mask for bifurcation
    img_grey = cv2.imread("prototypes/bif.jpg", cv2.IMREAD_GRAYSCALE)
    bif_mask = cv2.threshold(img_grey, 128, 255, cv2.THRESH_BINARY)[1]
    #load mask for termination
    img_grey = cv2.imread("prototypes/term.jpg", cv2.IMREAD_GRAYSCALE)
    term_mask = cv2.threshold(img_grey, 128, 255, cv2.THRESH_BINARY)[1]

    #generate bifurcations
    morph_bifurcations = delete_too_close_minutiae(morph_bifurcations)
    for bifurcation in morph_bifurcations:
        morph_res = insert_minutiae(morph_res, bifurcation, bif_mask, morph_ori, morph_freq)
    #morph_res = insert_minutiae(morph_res, morph_bifurcations[0], bif_mask, morph_ori, morph_freq)


    
    #generate terminations
    morph_terminations = delete_too_close_minutiae(morph_terminations, 50)
    for termination in morph_terminations:
        morph_res = insert_minutiae(morph_res, termination, term_mask, morph_ori, morph_freq)
    
    cv2.imshow("okok", morph_res)

    cv2.waitKey(0)
    cv2.destroyAllWindows()