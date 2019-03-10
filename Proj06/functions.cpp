////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #06   Vector
//
//  Define the head File "iostream" and "vector"
//    use the C++ Standard Library headers
//    the vector is vector tools
//
//  Defining function:
//    print_vector, four_corner_sum, column_order, rotate_rows_up, matrix_ccw_rotate, max_column_diff, trapped_values
//
//    print_vector: print the vector to the provided stream, returning that stream.
//    four_corner_sum: return the sum of the 4 corners of the provided 1D vector.
//    column_order: return a new vector that is a reordering of the original 1D vector in column order.
//    rotate_rows_up: return a new vector that is a rotation of the 2D matrix rows up by one.
//    matrix_ccw_rotate: return a new 1D vector that is a rotation of the entire 2D matrix counter-clockwise 90 degrees.
//    max_column_diff: Take the sum of each column. Return the max difference.
//    trapped_values: the value is trapped. return the number of trapped values.
//
////////////////////////////////////////////////////////////////////////////////

// whatever includes you need
#include "functions.h"

#include <iostream>  // the head File
using std::ostream;  // C++ STL

#include <vector>  // the head File
using std::vector;  // C++ STL

// print the vector to the provided stream, returning that stream.
ostream& print_vector(const vector<long>& v, ostream& out) {

    // for loop in every vector
    for (auto i = 0; i < v.size(); ++i) {

        out << v[i];

        if (i == v.size() - 1)
            break;

        out << ",";
    }

    // not cout
    return out;
}

// return the sum of the 4 corners of the provided 1D vector.
long four_corner_sum(const vector<long>& v, int rows, int cols) {

    // if there are less than either two rows or two columns (thus no corners), return 0.
    if (rows < 2 or cols < 2)
        return 0;

    long result = v[0];
    result += v[cols - 1];
    result += v[(rows - 1) * cols];
    result += v[(rows - 1) * cols + (cols - 1)];

    // interpreted as a 2D matrix with provided row and column count.
    return result;
}

// return a new vector that is a reordering of the original 1D vector in column order.
vector<long> column_order(const vector<long>& v, int rows, int cols) {

    vector<long> vec;

    // Collect each column, first to last, and within the column in row order.
    for (int c = 0; c < cols; ++c) {

        for (int r = 0; r < rows; ++r)
            vec.push_back(v[r * cols + c]);
    }

    return vec;
}

// return a new vector that is a rotation of the 2D matrix rows up by one.
vector<long> rotate_rows_up(const vector<long>& v, int rows, int cols) {

    vector<long> vec;

    // if rows just 1.
    if (rows < 2)
        return vec;

    vec.insert(vec.begin(), v.begin() + cols, v.end());
    vec.insert(vec.end(), v.begin(), v.begin() + cols);

    return vec;
}

// return a new 1D vector that is a rotation of the entire 2D matrix counter-clockwise 90 degrees.
vector<long> matrix_ccw_rotate(const vector<long>& v, int rows, int cols) {

    vector<long> vec;

    // for loop in every cols
    for (int c = cols - 1; c >= 0; --c) {

        // for loop in every rows
        for (int r = 0; r < rows; ++r)
            vec.push_back(v[r * cols + c]);
    }

    return vec;
}

// Take the sum of each column.
long max_column_diff(const vector<long>& v, int rows, int cols) {

    long max = 0, min = 9999, local = 0;

    // for loop in every cols
    for (int c = 0; c < cols; ++c) {

        for (int r = 0; r < rows; ++r)
            local += v[r * cols + c];

        if (local > max)
            max = local;

        if (local < min)
            min = local;

        local = 0;
    }

    // Return the max difference.
    return max - min;
}

// if any of values in the 2D matrix have 4 neighbors (up, down, left, right) that are all greater than that value.
long trapped_values(const vector<long>& v, int rows, int cols) {

    long num = 0;

    // two for loop in vector
    for (int r = 0; r < rows; ++r) {

        for (int c = 0; c < cols; ++c) {

            long up = v[(r - 1) * cols + c], down = v[(r + 1) * cols + c];
            long left = v[r * cols + c - 1], right = v[r * cols + c + 1];
            long value = v[r * cols + c];

            if (c == 0) left = v[r * cols + cols - 1];  // if col is 0.
            if (c == cols - 1) right = v[r * cols];  // if col is cols.
            if (r == 0) up = v[(rows - 1) * cols + c];  // if row is 0.
            if (r == rows - 1) down = v[c];  // if row is rows.

            if (value < up and value < down and value < left and value < right)
                num += 1;
        }
    }

    // the value is trapped. return the number of trapped values.
    return num;
}
