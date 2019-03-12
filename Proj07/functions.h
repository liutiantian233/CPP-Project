#ifndef PROJECT07_FUNCTIONS_H
#define PROJECT07_FUNCTIONS_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::ostream;

#include <map>
using std::map;

using map_type = map<string, long>;

ostream& print_vector(ostream &out, const vector<string> &v);
string clean_word(const string&);
vector<string> split(const string &s, char delim = ' ');
bool process_words(map_type&, string);
ostream& print_map(ostream& out, const map_type& m);
double jac_similarity(const map_type &m1, const map_type &m2);
double calc_norm_factor(const map_type &m1);
double cosine_similarity_tf(const map_type &m1, const map_type &m2);

#endif //PROJECT07_FUNCTIONS_H
