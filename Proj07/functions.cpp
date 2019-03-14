////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #07   Document Similarity
//
//  Define the head File "iostream" "vector" "string" "map" "fstream" "set" "algorithm" and "cmath"
//    use the C++ Standard Library headers
//    the "vector" "string" "map" "fstream" "set" "algorithm" and "cmath" are c++ tools
//
//  Defining function:
//    print_vector, clean_word, split, print_map, process_words, jac_similarity, calc_norm_factor, cosine_similarity_tf
//
//    print_vector: print the contents of the vector <string> to the parameter ostream. Return the ostream used.
//    clean_word: Create a new string where you remove any non-alphabetic characters and lower case everything.
//    split: Take in the string, return a vector where the string is split by the parameter character delim.
//    print_map: Like print_vector above, print the contents of the map to the parameter ostream.
//    process_words: records it in the map where the key of the map is the string and
//                   the value of the map is how many times that string occurred.
//    jac_similarity: Takes in two maps (representing the result of process_words on two documents).
//    calc_norm_factor: For a map created by process_words. Return the norm factor.
//    cosine_similarity_tf: Calculate the term frequency cosine similarity for
//                          two maps created by process_words as described above.
//
////////////////////////////////////////////////////////////////////////////////

// whatever includes you need
#include "functions.h"

#include <iostream>  // the head File
using std::ostream;  // C++ STL

#include <string>  // the head File
using std::string;  // C++ STL

#include <vector>  // the head File
using std::vector;  // C++ STL

#include <map>  // the head File
using std::map;  // C++ STL

#include <fstream>  // the head File
using std::ifstream;  // C++ STL

#include <set>  // the head File
using std::set;  // C++ STL

#include <algorithm>  // the head File
using std::set_intersection;  // C++ STL

#include <cmath>  // the head File

// print the contents of the vector <string> to the parameter ostream. Return the ostream used.
ostream& print_vector(ostream &out, const vector<string> &v) {
    for (auto i = 0; i < v.size(); ++i) {
        out << v[i];

        // if index in the end.
        if (i == v.size() - 1)
            break;
        out << ",";
    }
    return out;
}

// Take in a string. Create a new string where you remove any non-alphabetic characters and lower case everything.
string clean_word(const string& s) {
    string str;

    // for loop in the every char.
    for (auto c : s) {
        if (isalpha(c)) {
            char ch = static_cast<char>(tolower(c));
            str += ch;
        }
    }

    // Return that new string.
    return str;
}

// Take in the string, return a vector where the string is split by the parameter character delim.
vector<string> split(const string &s, char delim) {

    // Note the default is only provided in the header, not the definitions.
    vector<string> v;
    string str = s;

    // for loop in the every char.
    for (char c : s) {
        if (c == delim) {
            auto index = str.find(delim);  // to find the index of delim
            v.push_back(str.substr(0, index));
            str = str.substr(index + 1);
        }
    }
    v.push_back(str);
    return v;
}

// Like print_vector above, print the contents of the map to the parameter ostream.
ostream& print_map(ostream& out, const map_type& m) {
    auto index = 0;

    // for loop in every item.
    for (const auto &item : m) {
        index += 1;
        out << item.first << ":" << item.second;  // the item is Iterator

        // the Iterator in the end
        if (index == m.size())
            break;
        out << ",";
    }

    // Return the ostream used.
    return out;
}

// records it in the map where the key of the map is the string and
// the value of the map is how many times that string occurred.
bool process_words(map_type& m, string s) {
    string data;
    vector<string> vec;
    ifstream file;
    file.open(s);

    // if the file represented by the string cannot be opened,
    // the function returns false and makes no changes to the map.
    while (getline(file, data)) {

        // The function opens the file, reads the file one line at a time, splits the line.
        vector<string> v = split(data);
        vec.insert(vec.end(), v.begin(), v.end());
    }

    // cleans each word.
    for (const auto &v : vec) {
        string str = clean_word(v);

        // if there are str
        if (!m.count(str))
            m[str] = 1;
        else
            m[str] += 1;
    }
    file.close();

    // Otherwise the map is updated as indicated and the function returns true.
    return !vec.empty();
}

// Takes in two maps (representing the result of process_words on two documents).
double jac_similarity(const map_type &m1, const map_type &m2) {
    auto set1 = m1.size(), set2 = m2.size();
    set<string> s1, s2, set;

    // Using only the keys it calculates the jac similarity as described.
    for (const auto &pair : m1)
        s1.insert(pair.first);

    for (const auto &pair : m2)
        s2.insert(pair.first);

    // use the algorithm about set
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(set, set.begin()));
    auto set3 = set.size();

    // Returns the similarity.
    return (static_cast<double>(set3) / (set1 + set2 - set3));
}

// For a map created by process_words.
double calc_norm_factor(const map_type &m1) {
    double index = 0;

    // calculate the norm factor of the map / document as shown above (the square root of the frequencies squared).
    for (const auto &pair : m1)
        index += pow(pair.second, 2);

    // Return the norm factor.
    return pow(index, 0.5);
}

// Calculate the term frequency cosine similarity for two maps created by process_words as described above.
double cosine_similarity_tf(const map_type &m1, const map_type &m2) {
    double nf1 = calc_norm_factor(m1), nf2 = calc_norm_factor(m2), result = 0;
    map<string, vector<double>> m;

    // two for loop to get new map
    for (const auto &map : m1) {
        string key = map.first;
        m[key].push_back(map.second / nf1);
    }
    for (const auto &map : m2) {
        string key = map.first;
        m[key].push_back(map.second / nf2);
    }

    // for loop in the new map
    for (const auto &map : m) {

        // the map value have more than one
        if (map.second.size() > 1) {
            result += map.second[0] * map.second[1];
        }
    }

    // Return the similarity.
    return result;
}
