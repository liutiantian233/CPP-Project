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

# Steganography

## Embedding

We are also going to be doing a little bit of cryptography of a kind slightly different than project 5. We are going to hide information in an image. See [link](https://en.wikipedia.org/wiki/Steganography). We are going to take 2 PGM images, **plain** and **secret** and modify the original **plain** to hide **secret** within. The rules to modify **plain** are as follows.

1. We assume that **secret** is the same size or smaller than **plain**.
2. We also assume that **secret** (when extracted from **plain**) will be visible as a black and white image. That is, once **secret** is embedded what we can extract is a black and white image.
3. We examine each pixel in **secret** and modify the corresponding pixel (row and column) of **plain** as follows:
   1. If the corresponding pixel from the **secret** image is 0, then the parity of the corresponding **plain** pixel must be set to even.
      1. If the **plain** pixel is already even, then it is not modified otherwise the **plain** pixel is updated to its original value - 1 so that it is even.
   2. If the **secret** pixel is non-0, then the parity of the corresponding **plain** pixel must be set to odd.
      1. If it's already odd, then the corresponding pixel of **plain** is not modified otherwise the **plain** pixel is updated to its original value + 1 so that it is odd.
      2. Of course, we have to ensure that the `max_value` of the **plain** image is preserved, so if the **plain** pixel is already at `max_value`, then 1 is subtracted.

Here is an example **plain** image.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-8.png)

And an example **secret** image.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-9.png)

The result of embedding the **secret** image in the **encoded** image is

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-10.png)

## Extracting

We can extract the **secret** image embedded in the modified **plain** image fairly straightforwardly. We create a new image (let's call it **extracted**) as follows:

1. We create a new image with the column and row values of **plain**.
2. For each pixel in **plain** we examine its parity:
   1. if the parity of the **plain** pixel is odd, we write the provided `max_value` as the corresponding pixel of the **extracted** image.
   2. if the parity of the **plain** pixel is even, we write 0 as the corresponding pixel of the **extracted** image.

Note that some information is lost in this process. We create **extracted** as essentially a black and white value image (it has only two pixel values, `0` and `max_value` at each pixel) even though **secret** may have a broader set of values (more gray values). Further, if **plain** was larger than **secret** there will be corresponding noise in the **extracted** image. Not random noise, but pixels set to values that are not relevant to **secret**.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-11.png)

# Problem Statement

You are going to create an `Image struct` that will allow you to read, write, convolve (in various ways), embed and subsequently extract a PGM image.

# Program Specifications

You will be provided with a proj08-struct.h to start with but you can modify that file as long as the basic types for the listed function members are maintained. You must provide both the resulting proj08-struct.cpp and the proj08-struct.h file. I will also provide some sample PGM images so you can see the results of your work better.

# Image struct

- `Image()`: default constructor is in the header and takes the C++ default

- `Image(string f_name)`: constructor, reads in the PGM file into the class instance. It:
  - sets the `max_value`, `height_` and `width_` given in the file.
  - it then reads in every individual pixel value into the `vector<vector<long>> v_`. More on that in the notes section.

- `void write_image(string f_name)`: method, writes out the contents of the class instance into the given file as a properly configured PGM file. If you write it, you should be able to read it back in and view it using **paint.net**.

- `Image convolve(vector<vector<long>> mask, long divisor = 1, long whiten = 0)`: method. Note that `div` and `whiten` should have defaults in the header file but **should not** be provided in the class cpp file (it's a compile error if you do). This is the guts of the whole thing. This creates in a `new_image` (the one that you write into) using the provided `mask` which is the convolution mask. You apply the mask to the old image, setting the new pixels in the new image by passing the mask over all the pixels in the old image (the one the `this` pointer points to) and doing the calculation as described. The `new_image` is returned from the function.
  - if any new pixel calculation is greater than `max_value`, that pixel is set to `max_value` in the new image.
  - if any new pixel calculation is less than `0`, that pixel is set to `0` in the new image.
  - for each pixel calculation, the total value of the pixel calculation is divided by the parameter `divisor` (see the blur method).
  - for each pixel calculation, the parameter `whiten` is added the total value of the pixel calculation (see the `edge_detect` method).
  - as stated, unavailable neighbors are assumed to be 0 for edge pixels.

- `Image sharpen()`: method. Applies the `3 * 3` mask below to create the new image. Calls `convolve`. When calling `convolve`, it takes defaults on `div` and `whiten`. It returns a new `Image`.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-12.png)

- `Image edge_detect()`: method. Applies the `3 * 3` mask below to create the new image. Calls `convolve`. When calling `convolve`, it takes defaults on `divisor` but the image tends to be dark so it provides a `whiten` to brighten the resulting `Image`. Use `whiten = 50`. It returns a new `Image`.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-13.png)

- `Image blur()`: method. Applies the `3 * 3` mask below to create the new image. Calls `convolve`. When calling `convolve`, it takes defaults on `whiten` but mask always overshoots the `max_value`. To compensate we provide a `divisor = 9` (to normalize the result, averaging the pixel across its 8 neighbors). It returns a new Image.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-14.png)

- `Image emboss()`: method. Applies the `3 * 3` mask below to create the new image. Calls `convolve`. When calling `convolve`, it takes defaults on `divisor` and `whiten`. It returns a new `Image`.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj08/Proj08-15.png)

- `void embed(const Image& secret)`: method. Takes the **secret** image by `const&`, and embeds it in the **plain** image (the object on which it is called).
- `Image extract(long max_value)`: method. This function returns an image which is extracted from the pixels in the calling object (referred to by the `this` pointer). The `max_value` of this image is set to `max_value`, and the dimensions are the same as the called image object. Values of pixels in the resulting image are either `0` or `max_value`.
