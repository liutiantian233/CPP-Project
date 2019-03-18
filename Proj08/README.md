# Image Stuff

Perform some image processing on existing image files. First experience with C++ structs / classes and more work with 2D vectors.

## Background

Image processing is an interesting but typically complicated process. Even reading in and writing out images can be a chore without library support.

However, there are some simple image representation formats that are text files and with which we can do some simple manipulation.

## PNM files

There is a class of files called Netpbm for portable any format (PNM) files that can represent an image as a text file where each individual pixel is coded in the file. See [link](https://en.wikipedia.org/wiki/Netpbm_format) for more details.

They include:

- pbm files which are used to represent black and white images
- pgm files which are used to represent graymap images
- ppm files which are used to represent color images

The advantages to these kinds of files are their portability and easy access for image manipulation. Their clear downside is their size. These files can get very large and many other image formats work with ways to reduce the size of image files while maintaining their quality.

## PGM files

We are going to work with PGM files, graymap files. In a graymap file, each pixel is represented by a number from 0 to 255 (allowing the number to be stored in a single byte). The value 0 represents pure black, the value 255 pure white and the integer values in between represent shades of gray. If you ever had a black-and-white television, this was the kind of image it displayed. Most OS support PGM files pretty directly so viewing them is not really very hard.

Be careful that you work with a PGM ascii file. There is a binary file format as well that you cannot easily edit.

A PGM file is a text file with a fairly simple format (see [link](https://en.wikipedia.org/wiki/Netpbm_format#PGM_example) for details):

- a magic number which is always P2
  - a P5 magic number is the non-ascii version. Do not use one of those!
- two integers, space separated, that represent respectively the `x_size` and `y_size`, the dimensions, of the image.
- another integer, also space separated, the `max_gray` that represents the maximum gray value in the image.
- what follows is, for each row a series of space separated integers in the range `0` to `max_gray`.
  - there are `x_size` values in the row
  - there are `y_size` rows
- comments can occur anywhere in the file. If so, then the first character of that line is a `#`.
  - clearly, comments are ignored.
- separators can be white space, line feeds, stuff that is normal for C++ input.
- I have seen recommendations that no line should be more than 70 chars wide, but I have personally written out pgm images that are `512 * 512` and wrote each row as a single line without any issue. For this project, each row of the image should be written on a single line.

Here is an example.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-1.png)

It is a very small image only `5 * 5` pixels but if you blow it up it looks like:

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-2.png)

If you want to view these on the machines, go to the start menu, all apps and open **paint.net**. Then us the open menu on **paint.net** to open the file you wish to look at. Remember, these `5 * 5` files are very, very small. Some bigger files are provided in the directory for you to look at.

# Convolution

**Convolution, see [link](https://en.wikipedia.org/wiki/Kernel_(image_processing)) for details.**

Convolution, at least for images, creates a new single pixel based on some combination of values from its near neighbors and itself. This operation is performed for every pixel in the image.

When you do a convolution, you generate a new image from the old image based on the operations described below.

These operations are represented by a small matrix, called the kernel or convolution mask that represents these neighbor operations. For each pixel, you multiply each old pixel's value by its mask value, including the old pixel itself, and sum all those values up for the new pixel value. For example, let's take our simple image and apply a sharpen mask to the middle pixel with the value 122 (red) against the 8 neighbors (green). We want to calculate the new value for the 122 pixel in a modified image. To do so we use the mask matrix values and multiply the mask value with the appropriate neighbor, including the pixel itself. We sum them all up and that is the new value!

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-3.png)

In row order of the mask, we get the equation:

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-4.png)

The new pixel in the new image at the same location of the old pixel will have the value 488. But wait! 488 is larger than the `max_gray` we indicated in the file. So that new pixel's value gets reset to the `max_gray`, 245. If the calculated new pixel had been less than 0, we would have set it to 0.

We do this for every pixel, calculating a new pixel value based on the old pixel's neighbors and a convolution mask. The result is a new image. You can imagine sliding the mask along the original image one pixel at a time, doing the calculation and then generating a new pixel in a new image. A great web site that demonstrates this process is [link](http://setosa.io/ev/image-kernels/). Take a look!

# The edges

What to do on the edges of an image? Pixels on an edge do not have the required number of neighbors to make the calculation. We have choices on how to handle this:

- shrink the image, so that we only calculate new pixels not on the image border.
- wrap the image, so that values on the opposite edge fill in.
- just treat the missing neighbors as 0.

We will do the latter. We will treat missing neighbors as 0. For example, for calculating the new pixel for 183 (where the bolded values of 0 are the image value for missing neighbors) in row order.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-5.png)

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-6.png)

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-7.png)

Again this gets reset to 245, the max gray value.
