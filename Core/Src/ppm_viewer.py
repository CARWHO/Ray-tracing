import matplotlib.pyplot as plt

img = plt.imread('output.ppm')
plt.imshow(img)
plt.axis('off')
plt.show()