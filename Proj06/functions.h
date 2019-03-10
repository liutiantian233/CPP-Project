#ifndef PROJECT06_PROJECT06_H
#define PROJECT06_PROJECT06_H

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

ostream& print_vector(const vector<long>& v, ostream& out);
long four_corner_sum(const vector<long>& v, int rows, int cols);

vector<long> column_order(const vector<long>& v, int rows, int cols);
vector<long> rotate_rows_up(const vector<long>& v, int rows, int cols);
vector<long> matrix_ccw_rotate(const vector<long>& v, int rows, int cols);

long max_column_diff(const vector<long>& v, int rows, int cols);
long trapped_values(const vector<long>& v, int rows, int cols);

#endif
