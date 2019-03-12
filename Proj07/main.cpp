#include <vector>
using std::vector;

#include <sstream>
using std::ostringstream;

#include <string>
using std::string;

#include <iostream>
using std::endl;

#include <map>
using std::map;

#include "functions.h"

int main() {
    vector<string> v = split("This is a test.");
    ostringstream os;
    print_vector(os, v) << endl;

    string test = clean_word("A1B2C3xyz!!");

    map_type m = {{"a", 1}, {"b", 2}, {"c", 3}};
    print_map(os, m) << endl;
    string s = os.str();

    std::cout << s;
}
