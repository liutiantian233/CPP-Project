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
