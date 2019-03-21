////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #08   Image Stuff
//
//  Define the head File "string" "fstream" "sstream" and head file
//    use the C++ Standard Library headers
//    the "string" "fstream" "sstream" are c++ tools
//
//  Defining class public function:
//    Image(string f_name), void write_image(string f_name), Image sharpen(), Image edge_detect()
//    Image blur(), Image emboss(), void embed(const Image& secret), Image extract(long max_value)
//
//  Defining class private function:
//    Image convolve(vector<vector<long>> mask, long divisor, long whiten)
//
//    Image(string f_name): constructor, reads in the PGM file into the class instance.
//                          to get the width and height and pixels.
//    void write_image(string f_name): writes out the contents of the class instance into the given file
//                                     as a properly configured PGM file.
//    Image convolve: method. This is the guts of the whole thing.
//                            This creates in a new_image (the one that you write into) using the
//                            provided mask which is the convolution mask.
//    Image sharpen(): method. When calling convolve, it takes defaults on div and whiten. It returns a new Image.
//    Image edge_detect(): method. When calling convolve, it takes defaults on divisor but the image tends to be dark
//                         so it provides a whiten to brighten the resulting Image. Use whiten = 50.
//                         It returns a new Image.
//    Image blur(): method. When calling convolve, it takes defaults whiten but mask always overshoots the max_value.
//                  To compensate we provide a divisor = 9. It returns a new Image.
//    Image emboss(): method. When calling convolve, it takes defaults on divisor and whiten. It returns a new Image.
//    void embed(const Image& secret): method. Takes the secret image by const&,
//                                     and embeds it in the plain image (the object on which it is called).
//    Image extract(long max_value): method. This function returns an image which is extracted from the pixels
//                                   in the calling object (referred to by the this pointer).
//
////////////////////////////////////////////////////////////////////////////////

// whatever includes you need
#include <string>  // the head File
using std::string;  // C++ STL

#include <fstream>  // the head File
using std::ifstream; using std::ofstream;  // C++ STL

#include <sstream>  // the head File
using std::stringstream;  // C++ STL

#include "functions.h"  // the head File

// constructor, reads in the PGM file into the class instance.
Image::Image(string f_name) {

    // use the ifstream to open file.
    ifstream f;
    f.open(f_name);
    string s, result;

    // while loop to Remove the # and P2
    while (getline(f, s))
        if (s[0] != '#' and s[0] != 'P')
            break;
    // to get the width and height
    width_ = std::stol(s.substr(0, s.find(' ')));
    height_ = std::stol(s.substr(s.find(' ') + 1));
    getline(f, s);
    max_val_ = std::stol(s);

    // the for loop in every line to get pixels.
    for (long h = 0; h < height_; ++h) {
        getline(f, s);
        vector<long> v;
        stringstream input(s);
        while (input >> result)
            v.push_back(std::stol(result));
        pixels_.push_back(v);
    }
    f.close();  // close the file
}

// method, writes out the contents of the class instance into the given file as a properly configured PGM file.
void Image::write_image(string f_name) const {

    // use the ofstream to write the file.
    ofstream f;
    f.open(f_name);

    // write one by one
    f << "P2" << endl;
    f << width_ << ' ' << height_ << endl;
    f << max_val_ << endl;

    // use the for loop to write on a line
    for (const auto &h : pixels_) {
        for (auto w : h)
            f << w << ' ';
        f << endl;  // change a new line
    }
    f.close();  // close the file
}

Image Image::convolve(vector<vector<long>> mask, long divisor, long whiten) const {

    // creates in a new_image
    Image new_image;
    new_image.width_ = width_;
    new_image.height_ = height_;
    new_image.max_val_ = max_val_;

    // for loop in every line
    for (size_t line_pixel = 0; line_pixel < pixels_.size(); ++line_pixel) {
        vector<long> v;

        // for loop in every number in a line
        for (size_t col_pixel = 0; col_pixel < pixels_[line_pixel].size(); ++col_pixel) {

            // number around the one number
            long top = 0, under = 0, left = 0, right = 0, total = 0;
            // get the up down left right number
            if (line_pixel != 0) top = pixels_[line_pixel - 1][col_pixel];
            if (line_pixel != pixels_.size() - 1) under = pixels_[line_pixel + 1][col_pixel];
            if (col_pixel != 0) left = pixels_[line_pixel][col_pixel - 1];
            if (col_pixel != pixels_[line_pixel].size() - 1) right = pixels_[line_pixel][col_pixel + 1];

            // number around the one number
            long top_left = 0, top_right = 0, under_left = 0, under_right = 0;
            // get the Corner position number
            if (line_pixel != 0 and col_pixel != 0)
                top_left = pixels_[line_pixel - 1][col_pixel - 1];
            if (line_pixel != 0 and col_pixel != pixels_[line_pixel].size() - 1)
                top_right = pixels_[line_pixel - 1][col_pixel + 1];
            if (line_pixel != pixels_.size() - 1 and col_pixel != 0)
                under_left = pixels_[line_pixel + 1][col_pixel - 1];
            if (line_pixel != pixels_.size() - 1 and col_pixel != pixels_[line_pixel].size() - 1)
                under_right = pixels_[line_pixel + 1][col_pixel + 1];

            // get the total number
            total += mask[0][0] * top_left + mask[0][1] * top + mask[0][2] * top_right;
            total += mask[1][0] * left + mask[1][1] * pixels_[line_pixel][col_pixel] + mask[1][2] * right;
            total += mask[2][0] * under_left + mask[2][1] * under + mask[2][2] * under_right;
            total = (total / divisor) + whiten;

            // If it is a special case
            if (total > max_val_) total = max_val_;
            if (total < 0) total = 0;
            
            // push in the line
            v.push_back(total);
        }

        // push the new image pixel
        new_image.pixels_.push_back(v);
    }
    return new_image;  // return a new image
}

// method. When calling convolve, it takes defaults on div and whiten. It returns a new Image.
Image Image::sharpen() const {
    return convolve(vector<vector<long>> {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});
}

// method. When calling convolve, it takes defaults on divisor but Use whiten = 50. It returns a new Image.
Image Image::edge_detect() const {
    return convolve(vector<vector<long>> {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}}, 1, 50);
}

// method. When calling convolve, it takes defaults whiten but mask always overshoots the max_value.
Image Image::blur() const {
    // To compensate we provide a divisor = 9. It returns a new Image.
    return convolve(vector<vector<long>> {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 9);
}

// method. When calling convolve, it takes defaults on divisor and whiten. It returns a new Image.
Image Image::emboss() const {
    return convolve(vector<vector<long>> {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}});
}

// method. Takes the secret image by const&, and embeds it in the plain image (the object on which it is called).
void Image::embed(const Image& secret) {

    // use the for loop in every line in the pixel.
    for (size_t y = 0; y < secret.pixels_.size(); ++y) {
        // use the for loop in every number on a line.
        for (size_t x = 0; x < secret.pixels_[y].size(); ++x) {

            // if it is a 0
            if (secret.pixels_[y][x] == 0) {
                // if it is odd
                if (pixels_[y][x] % 2 != 0)
                    pixels_[y][x] -= 1;
            } else {  // not 0
                // if it is even
                if (pixels_[y][x] % 2 == 0) {
                    pixels_[y][x] += 1;

                    // if it already at max_val_
                    if (pixels_[y][x] > max_val_)
                        pixels_[y][x] = max_val_ - 1;
                }
            }
        }
    }
}

// method. This function returns an image which is extracted from the pixels in the calling object.
Image Image::extract(long max_value) const {

    // get a new Image
    Image new_image;
    new_image.width_ = width_;
    new_image.height_ = height_;
    new_image.max_val_ = max_value;

    // for loop in every line at pixel
    for (const auto &pixel : pixels_) {
        vector<long> v;
        // for loop in every number at line
        for (long x : pixel) {

            // if it is a odd
            if (x % 2 != 0)
                v.push_back(max_value);
            else  // if it is a even
                v.push_back(0);
        }

        // push in the new Image
        new_image.pixels_.push_back(v);
    }
    return new_image;
}
