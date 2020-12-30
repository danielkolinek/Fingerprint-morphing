import matplotlib.pyplot as plt
import cv2

from functions.minutiae import drawMinutiae
from functions.coreDetection import drawDetectedCore
from functions.cutline import drawCutline
class PlotRes():
    fingerprint_1_start = None
    fingerprint_2_start = None
    fingerprint_1_end = None
    fingerprint_2_end = None
    orientation_field_1 = None
    orientation_field_2 = None
    alignment_draw = None
    intersection_gray_1 = None
    intersection_gray_2 = None
    freq_1 = None
    freq_2 = None

    def noneCheck(self, var):
        return var is not None

    def drawRes(self, minutiae_1 = None, minutiae_2 = None, barycenter = None, cutline = None ,morph_res = None):
        ##### plot results #####
        ## plot alighning part
        fig = plt.figure()
        fig.canvas.set_window_title('Results of aligning')
        # starting fingerprints cutted
        if(self.noneCheck(self.fingerprint_1_start) and self.noneCheck(self.fingerprint_2_start)):
            # grayscale fingerprints
            fig.set_figheight(15)
            gray1 = fig.add_subplot(3,2,1) #img1
            gray1.imshow(self.fingerprint_1_start, cmap='gray')
            gray2 = fig.add_subplot(3,2,2) #img2
            gray2.imshow(self.fingerprint_2_start, cmap='gray')
        #orientatiion fields
        if(self.noneCheck(self.orientation_field_1) and self.noneCheck(self.orientation_field_2)):
            or1 = fig.add_subplot(3,2,3)
            or1.imshow(self.orientation_field_1, cmap='gray')
            or2 = fig.add_subplot(3,2,4)
            or2.imshow(self.orientation_field_2, cmap='gray')
        # alignment        
        if(self.noneCheck(self.alignment_draw)):
            ali = fig.add_subplot(3,2,5)
            ali.imshow(self.alignment_draw, cmap='gray')

        ## plot optimal cutline part
        fig_1 = plt.figure()
        fig_1.canvas.set_window_title('Results of cutline')
        fig_1.set_figheight(15)
        # intersecting fingerprints
        if(self.noneCheck(self.intersection_gray_1) and self.noneCheck(self.intersection_gray_2)):
            gray1_1 = fig_1.add_subplot(3,3,1)
            gray1_1.imshow(self.intersection_gray_1, cmap='gray')

            gray2_2 = fig_1.add_subplot(3,3,4)
            gray2_2.imshow(self.intersection_gray_2, cmap='gray')
        # ridge frequency
        if(self.noneCheck(self.freq_1) and self.noneCheck(self.freq_2)):
            freq_1_draw = fig_1.add_subplot(3,3,2)
            freq_1_draw.imshow(self.freq_1*255, cmap='gray')

            freq_2_draw = fig_1.add_subplot(3,3,5)
            freq_2_draw.imshow(self.freq_2*255, cmap='gray')
        # plot miniatues
        if(self.noneCheck(minutiae_1) and self.noneCheck(minutiae_2)):
            minutiae_1_draw = fig_1.add_subplot(3,3,3)
            minutiae_1_draw.imshow(drawMinutiae(self.intersection_gray_1, minutiae_1), cmap='gray')

            minutiae_2_draw = fig_1.add_subplot(3,3,6)
            minutiae_2_draw.imshow(drawMinutiae(self.intersection_gray_2, minutiae_2), cmap='gray')
        # plot cutline on fingerprint 1 and 2
        if(self.noneCheck(cutline) and self.noneCheck(self.fingerprint_1_end) and self.noneCheck(self.fingerprint_2_end)):
            cutline_img = drawDetectedCore(self.fingerprint_1_end, barycenter) # .astype('uint8')
            cutline_img = drawCutline(cutline, cutline_img)
            cutline_draw = fig_1.add_subplot(3,3,7)
            cutline_draw.imshow(cutline_img, cmap='gray')

            cutline_img = drawDetectedCore(self.fingerprint_2_end, barycenter) # .astype('uint8')
            cutline_img = drawCutline(cutline, cutline_img)
            cutline_draw = fig_1.add_subplot(3,3,8)
            cutline_draw.imshow(cutline_img, cmap='gray')
        # plot morph
        if(self.noneCheck(morph_res)):
            morph_draw = fig_1.add_subplot(3,3,9)
            #cv2.imshow("morph", morph_res.astype('uint8'))
            morph_draw.imshow(morph_res, cmap='gray')

        #show plots
        plt.show()
        