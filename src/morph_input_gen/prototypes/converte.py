import cv2

img_grey = cv2.imread("bif.jpg", cv2.IMREAD_GRAYSCALE)
thresh = 128
img_binary = cv2.threshold(img_grey, thresh, 255, cv2.THRESH_BINARY)[1]

cv2.imshow("okok", img_binary)

cv2.waitKey(0) 
cv2.destroyAllWindows() 

