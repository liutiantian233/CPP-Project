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

#include <fstream>
using std::ifstream;

#include "functions.h"

int main() {
    vector<string> v = split("This is a test.");
    ostringstream os;
    print_vector(os, v) << endl;
    map_type m;
    bool result = process_words(m, "/Users/one/Documents/CSE232/Project07/file1.txt");
    print_map(os, m) << endl;
    string s = os.str();
    std::cout << s;

    map_type m1, m2;
    bool result1 = process_words(m1, "/Users/one/Documents/CSE232/Project07/file1.txt");
    bool result2 = process_words(m2, "/Users/one/Documents/CSE232/Project07/file2.txt");
    double sim1 = jac_similarity(m1, m2);
    double sim2 = cosine_similarity_tf(m1, m2);
    std::cout << sim2;
}
