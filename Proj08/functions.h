// the head begin
#ifndef PROJECT08_FUNCTIONS_H
#define PROJECT08_FUNCTIONS_H

#include <vector>  // the head File
using std::vector;  // C++ STL

#include <string>  // the head File
using std::string;  // C++ STL

#include <iostream>  // the head File
using std::cin; using std::cout; using std::endl;  // C++ STL

// Defining the new struct
struct Image {

public:  // could be private, testing easier as public
    vector<vector<long>> pixels_;

    // Defining the default
    long height_ = 0;
    long width_ = 0;
    long max_val_ = 0;
    
    Image convolve(vector<vector<long>> mask, long divisor = 1, long whiten = 0) const;  // Defining the default

public:  // this is public function
    Image() = default;  // Defining the default
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
