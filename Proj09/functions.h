#ifndef PROJECT09_FUNCTIONS_H
#define PROJECT09_FUNCTIONS_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <initializer_list>
using std::initializer_list;

#include <iostream>
using std::ostream;

struct Element{

public:
    string key_;
    vector<string> values_;
    Element() = default;
    Element(string key, initializer_list<string> values);
    bool operator == (const Element&) const;
    friend ostream&operator << (ostream&, Element&);
};

class MVM{

public:
    vector<Element> data_;
    vector<Element>::iterator find_key(string);
    vector<string> find_value(string);

public:
    MVM() = default;
    MVM(initializer_list<Element>);
    size_t size();
    bool add(string, string);
    bool remove_key(string);
    vector<string> remove_value(string);
    friend ostream&operator << (ostream&, MVM&);
};

#endif //PROJECT09_FUNCTIONS_H
