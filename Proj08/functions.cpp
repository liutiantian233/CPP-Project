#include <string>
using std::string;

#include <fstream>
using std::ifstream; using std::ofstream;

#include <sstream>
using std::stringstream;

#include "functions.h"

Image::Image(string f_name) {
    ifstream f;
    f.open(f_name);
    string s, result;
    while (getline(f, s))
        if (s[0] != '#' and s[0] != 'P')
            break;
    width_ = std::stol(s.substr(0, s.find(' ')));
    height_ = std::stol(s.substr(s.find(' ') + 1));
    getline(f, s);
    max_val_ = std::stol(s);
    for (long h = 0; h < height_; ++h) {
        getline(f, s);
        vector<long> v;
        stringstream input(s);
        while (input >> result)
            v.push_back(std::stol(result));
        pixels_.push_back(v);
    }
    f.close();
}

void Image::write_image(string f_name) const {
    ofstream f;
    f.open(f_name);
    f << "P2" << endl;
    f << width_ << ' ' << height_ << endl;
    f << max_val_ << endl;
    for (const auto &h : pixels_) {
        for (auto w : h)
            f << w << ' ';
        f << endl;
    }
    f.close();
}

Image Image::convolve(vector<vector<long>> mask, long divisor, long whiten) const {
    Image new_image;
    new_image.width_ = width_;
    new_image.height_ = height_;
    new_image.max_val_ = max_val_;
    for (size_t line_pixel = 0; line_pixel < pixels_.size(); ++line_pixel) {
        vector<long> v;
        for (size_t col_pixel = 0; col_pixel < pixels_[line_pixel].size(); ++col_pixel) {
            long top = 0, under = 0, left = 0, right = 0, total = 0;
            if (line_pixel != 0) top = pixels_[line_pixel - 1][col_pixel];
            if (line_pixel != pixels_.size() - 1) under = pixels_[line_pixel + 1][col_pixel];
            if (col_pixel != 0) left = pixels_[line_pixel][col_pixel - 1];
            if (col_pixel != pixels_[line_pixel].size() - 1) right = pixels_[line_pixel][col_pixel + 1];
            long top_left = 0, top_right = 0, under_left = 0, under_right = 0;
            if (line_pixel != 0 and col_pixel != 0)
                top_left = pixels_[line_pixel - 1][col_pixel - 1];
            if (line_pixel != 0 and col_pixel != pixels_[line_pixel].size() - 1)
                top_right = pixels_[line_pixel - 1][col_pixel + 1];
            if (line_pixel != pixels_.size() - 1 and col_pixel != 0)
                under_left = pixels_[line_pixel + 1][col_pixel - 1];
            if (line_pixel != pixels_.size() - 1 and col_pixel != pixels_[line_pixel].size() - 1)
                under_right = pixels_[line_pixel + 1][col_pixel + 1];
            total += mask[0][0] * top_left + mask[0][1] * top + mask[0][2] * top_right;
            total += mask[1][0] * left + mask[1][1] * pixels_[line_pixel][col_pixel] + mask[1][2] * right;
            total += mask[2][0] * under_left + mask[2][1] * under + mask[2][2] * under_right;
            total = (total / divisor) + whiten;
            if (total > max_val_) total = max_val_;
            if (total < 0) total = 0;
            v.push_back(total);
        }
        new_image.pixels_.push_back(v);
    }
    return new_image;
}

Image Image::sharpen() const {
    return convolve(vector<vector<long>> {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});
}

Image Image::edge_detect() const {
    return convolve(vector<vector<long>> {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}}, 1, 50);
}

Image Image::blur() const {
    return convolve(vector<vector<long>> {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 9);
}

Image Image::emboss() const {
    return convolve(vector<vector<long>> {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}});
}

void Image::embed(const Image& secret) {
    for (size_t y = 0; y < secret.pixels_.size(); ++y) {
        for (size_t x = 0; x < secret.pixels_[y].size(); ++x) {
            if (secret.pixels_[y][x] == 0) {
                if (pixels_[y][x] % 2 != 0)
                    pixels_[y][x] -= 1;
            } else {
                if (pixels_[y][x] % 2 == 0) {
                    pixels_[y][x] += 1;
                    if (pixels_[y][x] > max_val_)
                        pixels_[y][x] = max_val_ - 1;
                }
            }
        }
    }
}

Image Image::extract(long max_value) const {
    Image new_image;
    new_image.width_ = width_;
    new_image.height_ = height_;
    new_image.max_val_ = max_value;
    for (const auto &pixel : pixels_) {
        vector<long> v;
        for (long x : pixel) {
            if (x % 2 != 0)
                v.push_back(max_value);
            else
                v.push_back(0);
        }
        new_image.pixels_.push_back(v);
    }
    return new_image;
}
