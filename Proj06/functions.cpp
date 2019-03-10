////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #06   Vector
//
//  Define the head File "iostream" and "vector"
//    use the C++ Standard Library headers
//    the vector is vector tools
//
//  Defining function:
//    print_vector, four_corner_sum, column_order, rotate_rows_up, matrix_ccw_rotate, max_column_diff
//
//    lower_case: returns the lower case version of the input string s.
//    to_binary: returns 5 bit string that is the index of the character argument.
//    from_binary: returns the character that the 5 bit binary string bit_str represents.
//    check_message: returns true if there are at least 5x the count of characters in secret_message as in plaintext.
//    encode: plaintext and secret_message should be converted to lower case by lower_case.
//    decode: returns the original secret_message as a string.
//
//  Defining main function:
//    use the all function and switch case statement.
//
////////////////////////////////////////////////////////////////////////////////

// whatever includes you need
#include "proj06.h"

#include <iostream>  // the head File
using std::ostream;  // C++ STL

#include <vector>  // the head File
using std::vector;  // C++ STL

ostream& print_vector(const vector<long>& v, ostream& out) {

    for (auto i = 0; i < v.size(); ++i) {

        out << v[i];

        if (i == v.size() - 1)
            break;

        out << ",";
    }
    return out;
}

long four_corner_sum(const vector<long>& v, int rows, int cols) {

    if (rows < 2 or cols < 2)
        return 0;

    long result = v[0];
    result += v[cols - 1];
    result += v[(rows - 1) * cols];
    result += v[(rows - 1) * cols + (cols - 1)];

    return result;
}

vector<long> column_order(const vector<long>& v, int rows, int cols) {

    vector<long> vec;

    for (int c = 0; c < cols; ++c) {

        for (int r = 0; r < rows; ++r)
            vec.push_back(v[r * cols + c]);
    }

    return vec;
}

vector<long> rotate_rows_up(const vector<long>& v, int rows, int cols) {

    vector<long> vec;

    if (rows < 2)
        return vec;

    vec.insert(vec.begin(), v.begin() + cols, v.end());
    vec.insert(vec.end(), v.begin(), v.begin() + cols);

    return vec;
}

vector<long> matrix_ccw_rotate(const vector<long>& v, int rows, int cols) {

    vector<long> vec;

    for (int c = cols - 1; c >= 0; --c) {

        for (int r = 0; r < rows; ++r)
            vec.push_back(v[r * cols + c]);
    }

    return vec;
}

long max_column_diff(const vector<long>& v, int rows, int cols) {

    long max = 0, min = 9999, local = 0;

    for (int c = 0; c < cols; ++c) {

        for (int r = 0; r < rows; ++r)
            local += v[r * cols + c];

        if (local > max)
            max = local;

        if (local < min)
            min = local;

        local = 0;
    }

    return max - min;
}

long trapped_values(const vector<long>& v, int rows, int cols) {

    long num = 0;

    for (int r = 0; r < rows; ++r) {

        for (int c = 0; c < cols; ++c) {

            long up = v[(r - 1) * cols + c], down = v[(r + 1) * cols + c];
            long left = v[r * cols + c - 1], right = v[r * cols + c + 1];
            long value = v[r * cols + c];

            if (c == 0) left = v[r * cols + cols - 1];
            if (c == cols - 1) right = v[r * cols];
            if (r == 0) up = v[(rows - 1) * cols + c];
            if (r == rows - 1) down = v[c];

            if (value < up and value < down and value < left and value < right)
                num += 1;
        }
    }

    return num;
}
