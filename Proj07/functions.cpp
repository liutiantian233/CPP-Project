#include "functions.h"

#include <iostream>
using std::ostream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <fstream>
using std::ifstream;

#include <set>
using std::set;

#include <algorithm>
using std::set_intersection;

#include <cmath>

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

bool process_words(map_type& m, string s) {
    string data;
    vector<string> vec;
    ifstream file;
    file.open(s);
    while (getline(file, data)) {
        vector<string> v = split(data);
        vec.insert(vec.end(), v.begin(), v.end());
    }
    for (const auto &v : vec) {
        string str = clean_word(v);
        if (!m.count(str))
            m[str] = 1;
        else
            m[str] += 1;
    }
    file.close();
    return !vec.empty();
}

double jac_similarity(const map_type &m1, const map_type &m2) {
    auto set1 = m1.size(), set2 = m2.size();
    set<string> s1, s2, set;
    for (const auto &pair : m1)
        s1.insert(pair.first);
    for (const auto &pair : m2)
        s2.insert(pair.first);
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(set, set.begin()));
    auto set3 = set.size();
    return (static_cast<double>(set3) / (set1 + set2 - set3));
}

double calc_norm_factor(const map_type &m1) {
    double index = 0;
    for (const auto &pair : m1)
        index += pow(pair.second, 2);
    return pow(index, 0.5);
}

double cosine_similarity_tf(const map_type &m1, const map_type &m2) {
    double nf1 = calc_norm_factor(m1), nf2 = calc_norm_factor(m2), result = 0;
    map<string, vector<double>> m;
    for (const auto &map : m1) {
        string key = map.first;
        m[key].push_back(map.second / nf1);
    }
    for (const auto &map : m2) {
        string key = map.first;
        m[key].push_back(map.second / nf2);
    }
    for (const auto &map : m) {
        if (map.second.size() > 1) {
            result += map.second[0] * map.second[1];
        }
    }
    return result;
}
