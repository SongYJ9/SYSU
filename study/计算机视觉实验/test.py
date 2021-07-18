import cv2, time
import numpy as np
import matplotlib.pyplot as plt

image = cv2.imread('c.png', 1) # read in BGR, so you should change to RGB next

image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB) # BGR to RGB

grayImage = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY) # RGB to gray

# Gradient

GradientKernelX = np.array([[-1, 1]], dtype = int)
GradientKernelY = np.array([[-1], [1]], dtype = int)

GradientX = cv2.filter2D(grayImage, cv2.CV_16S, GradientKernelX)
GradientY = cv2.filter2D(grayImage, cv2.CV_16S, GradientKernelY)

GradientAbsX = cv2.convertScaleAbs(GradientX)
GradientAbsY = cv2.convertScaleAbs(GradientY)
Gradient = cv2.addWeighted(GradientAbsX, 0.5, GradientAbsY, 0.5, 0)

# Roberts

RobertsKernelX = np.array([[1, 0], [0, -1]], dtype = int)
RobertsKernelY = np.array([[0, -1], [1, 0]], dtype = int)

RobertsX = cv2.filter2D(grayImage, cv2.CV_16S, RobertsKernelX)
RobertsY = cv2.filter2D(grayImage, cv2.CV_16S, RobertsKernelY)

RobertsAbsX = cv2.convertScaleAbs(RobertsX)
RobertsAbsY = cv2.convertScaleAbs(RobertsY)
Roberts = cv2.addWeighted(RobertsAbsX, 0.5, RobertsAbsY, 0.5, 0)

# Prewitt

PrewittKernelX = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]], dtype = int)
PrewittKernelY = np.array([[1, 1, 1], [0, 0, 0], [-1, -1, -1]], dtype = int)

PrewittX = cv2.filter2D(grayImage, cv2.CV_16S, PrewittKernelX)
PrewittY = cv2.filter2D(grayImage, cv2.CV_16S, PrewittKernelY)

PrewittAbsX = cv2.convertScaleAbs(PrewittX)
PrewittAbsY = cv2.convertScaleAbs(PrewittY)
Prewitt = cv2.addWeighted(PrewittAbsX, 0.5, PrewittAbsY, 0.5, 0)

# Sobel

SobelTime = time.time()

SobelKernelX = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], dtype = int)
SobelKernelY = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]], dtype = int)

SobelX = cv2.filter2D(grayImage, cv2.CV_16S, SobelKernelX)
SobelY = cv2.filter2D(grayImage, cv2.CV_16S, SobelKernelY)

SobelAbsX = cv2.convertScaleAbs(SobelX)
SobelAbsY = cv2.convertScaleAbs(SobelY)
Sobel = cv2.addWeighted(SobelAbsX, 0.5, SobelAbsY, 0.5, 0)

SobelTime = time.time() - SobelTime

'''

# or

SobelX2 = cv2.Sobel(grayImage, cv2.CV_16S, 1, 0)
SobelY2 = cv2.Sobel(grayImage, cv2.CV_16S, 0, 1)

SobelAbsX2 = cv2.convertScaleAbs(SobelX2)
SobelAbsY2 = cv2.convertScaleAbs(SobelY2)
Sobel2 = cv2.addWeighted(SobelAbsX2, 0.5, SobelAbsY2, 0.5, 0)

''' 

# Laplacian

LaplacianKernel = np.array([[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]], dtype = int)

Laplacian = cv2.filter2D(grayImage, cv2.CV_16S, LaplacianKernel)

Laplacian = cv2.convertScaleAbs(Laplacian)

'''

# or

Laplacian2 = cv2.Laplacian(grayImage, cv2.CV_16S, ksize = 3) # ksize = 3 or 5
Laplacian2 = cv2.convertScaleAbs(Laplacian2)

'''

# Canny

CannyTime = time.time()

Canny = cv2.GaussianBlur(grayImage, (3, 3), 0)
Canny = cv2.Canny(Canny, 50, 150)

CannyTime = time.time() - CannyTime

''' # figure_1

plt.subplot(221), plt.imshow(image), plt.title('image'), plt.axis('off')
plt.subplot(222), plt.imshow(GradientAbsX, cmap = plt.cm.gray), plt.title('GradientAbsX'),  plt.axis('off')
plt.subplot(223), plt.imshow(GradientAbsY, cmap = plt.cm.gray), plt.title('GradientAbsY'),  plt.axis('off')
plt.subplot(224), plt.imshow(Gradient, cmap = plt.cm.gray), plt.title('Gradient'),  plt.axis('off')
plt.show()

'''

''' # figure_2

plt.subplot(321), plt.imshow(image), plt.title('image'), plt.axis('off')
plt.subplot(322), plt.imshow(Roberts, cmap = plt.cm.gray), plt.title('Roberts'),  plt.axis('off')
plt.subplot(323), plt.imshow(Prewitt, cmap = plt.cm.gray), plt.title('Prewitt'),  plt.axis('off')
plt.subplot(324), plt.imshow(Sobel, cmap = plt.cm.gray), plt.title('Sobel'),  plt.axis('off')
plt.subplot(325), plt.imshow(Laplacian, cmap = plt.cm.gray), plt.title('Laplacian'),  plt.axis('off')
plt.subplot(326), plt.imshow(Canny, cmap = plt.cm.gray), plt.title('Canny'),  plt.axis('off')
plt.show()

'''

print(SobelTime, CannyTime)

#''' # figure 3

Canny = cv2.GaussianBlur(grayImage, (3, 3), 0)
Canny_0_150 = cv2.Canny(Canny, 0, 150)
Canny_50_150 = cv2.Canny(Canny, 50, 150)
Canny_100_150 = cv2.Canny(Canny, 100, 150)

plt.subplot(221), plt.imshow(image), plt.title('image'), plt.axis('off')
plt.subplot(222), plt.imshow(Canny_0_150, cmap = plt.cm.gray), plt.title('Canny_0_150'),  plt.axis('off')
plt.subplot(223), plt.imshow(Canny_50_150, cmap = plt.cm.gray), plt.title('Canny_50_150'),  plt.axis('off')
plt.subplot(224), plt.imshow(Canny_100_150, cmap = plt.cm.gray), plt.title('Canny_100_150'),  plt.axis('off')
plt.show()

#'''
