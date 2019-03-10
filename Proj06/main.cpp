#include <iostream>
using std::cout;
using std::endl;

#include <sstream>
using std::ostringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "functions.h"

int main() {
    vector<long> v {11, 12, 13, 14, 15, 21, 22, 23, 24, 25, 31, 32, 33, 34, 35, 41, 42, 43, 44, 45};
    ostringstream os;
    print_vector(v, os);

    int rows = 4;
    int cols = 5;
    long result1 = four_corner_sum(v, rows, cols);
    vector<long> result2 = column_order(v, rows, cols);
    vector<long> result3 = rotate_rows_up(v, rows, cols);
    vector<long> result4 = matrix_ccw_rotate(v, rows, cols);
    long result5 = max_column_diff(v, rows, cols);
    long result6 = trapped_values(v, rows, cols);
}
