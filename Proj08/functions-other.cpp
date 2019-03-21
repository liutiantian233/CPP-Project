#include <string>
using std::string;

#include <fstream>
using std::ifstream; using std::ofstream;

#include <sstream>
using std::stringstream;

#include "functions.h"

Image::Image(string f_name) {
    ifstream file(f_name);
    string str1, have_width_height, have_max;
    while (getline(file, str1)) {
        vector<long> v;
        string str2;
        if (str1[0] == '#' or str1[0] == 'P')
            continue;
        str1 += ' ';
        for (auto s : str1) {
            if (isdigit(s)) {
                str2 += s;
                continue;
            }
            if (!str2.empty()) {
                v.push_back(stol(str2));
                str2 = "";
            }
        }
        if (have_width_height.empty()) {
            width_ = v[0];
            height_ = v[1];
            have_width_height = "NONE";
            continue;
        }
        if (have_max.empty()) {
            max_val_ = v[0];
            have_max = "NONE";
            continue;
        }
        pixels_.push_back(v);
    }
    file.close();
}

void Image::write_image(string f_name) const {
    ofstream file(f_name);
    file << "P2" << endl << width_ << ' ' << height_ << endl << max_val_ << endl;
    for (const auto &y : pixels_) {
        for (auto x : y)
            file << x << ' ';
        file << endl;
    }
    file.close();
}

Image Image::convolve(vector<vector<long>> mask, long divisor, long whiten) const {
    Image new_image;
    new_image.width_ = width_;
    new_image.height_ = height_;
    new_image.max_val_ = max_val_;
    auto new_pixels_ = pixels_;
    vector<long> add_v(static_cast<unsigned long>(width_), 0);
    new_pixels_.insert(new_pixels_.begin(), add_v);
    new_pixels_.push_back(add_v);
    for (auto &new_pixel : new_pixels_) {
        new_pixel.insert(new_pixel.begin(), 0);
        new_pixel.push_back(0);
    }
    for (size_t y = 1; y < new_pixels_.size() - 1; ++y) {
        vector<long> v;
        for (size_t x = 1; x < new_pixels_[y].size() - 1; ++x) {
            long up, down, left, right, up_left, up_right, down_left, down_right, result;
            up = new_pixels_[y - 1][x];
            down = new_pixels_[y + 1][x];
            left = new_pixels_[y][x - 1];
            right = new_pixels_[y][x + 1];
            up_left = new_pixels_[y - 1][x - 1];
            up_right = new_pixels_[y - 1][x + 1];
            down_left = new_pixels_[y + 1][x - 1];
            down_right = new_pixels_[y + 1][x + 1];
            result = mask[0][0] * up_left + mask[0][1] * up + mask[0][2] * up_right;
            result += mask[1][0] * left + mask[1][1] * new_pixels_[y][x] + mask[1][2] * right;
            result += mask[2][0] * down_left + mask[2][1] * down + mask[2][2] * down_right;
            result = result / divisor + whiten;
            if (result > max_val_)
                result = max_val_;
            if (result < 0)
                result = 0;
            v.push_back(result);
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
