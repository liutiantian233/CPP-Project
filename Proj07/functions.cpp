#include "functions.h"

#include <iostream>
using std::ostream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

ostream& print_vector(ostream &out, const vector<string> &v) {

    for (auto i = 0; i < v.size(); ++i) {

        out << v[i];

        if (i == v.size() - 1)
            break;

        out << ",";
    }

    return out;
}

string clean_word(const string& s) {

    string str;

    for (auto c : s) {

        if (isalpha(c))
            str += tolower(c);
    }

    return str;
}

vector<string> split(const string &s, char delim) {
    vector<string> v;
    string str = s;

    for (char c : s) {

        if (c == delim) {
            auto index = str.find(delim);

            v.push_back(str.substr(0, index));
            str = str.substr(index + 1);
        }
    }
    v.push_back(str);

    return v;
}

ostream& print_map(ostream& out, const map_type& m) {

    auto index = 0;
    for (const auto &item : m) {
        index += 1;
        out << item.first << ":" << item.second;

        if (index == m.size())
            break;

        out << ",";
    }

    return out;
}

bool process_words(map_type& m, string s) {}
