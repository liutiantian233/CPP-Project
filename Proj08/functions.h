#ifndef PROJECT08_FUNCTIONS_H
#define PROJECT08_FUNCTIONS_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::cin; using std::cout; using std::endl;

struct Image {

public:  // could be private, testing easier as public
    vector<vector<long>> pixels_;
    long height_ = 0;
    long width_ = 0;
    long max_val_ = 0;
    Image convolve(vector<vector<long>> mask, long divisor = 1, long whiten = 0) const;

public:
    Image() = default;
    explicit Image(string f_name);
    void write_image(string f_name) const;
    Image sharpen() const;
    Image edge_detect() const;
    Image blur() const;
    Image emboss() const;
    void embed(const Image& secret);
    Image extract(long max_value) const;
};

#endif //PROJECT08_FUNCTIONS_H
