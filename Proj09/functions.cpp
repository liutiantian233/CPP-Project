////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #09   MVM
//
//  Define the head File "algorithm" "utility"
//    use the C++ Standard Library headers
//    the "algorithm" "utility" are C++ tools
//
//  Defining class public function in Element:
//    Element(string key, initializer_list<string> values): Take a string key and an initializer_list values
//                                                          and construct an Element with those values.
//    bool operator == (const Element&) const: Two Elements are equal if their two keys_ are equal
//                                             and if their two values_ are equal.
//    friend ostream&operator << (ostream&, Element&): output the Element to the provided ostream
//                                                     do not just print to cout.
//
//  Defining class public function in MVM:
//    vector<Element>::iterator find_key(string): returns an iterator that points to an Element in data_.
//                                                if data_.end(), the key is not there it is bigger than all keys.
//    vector<string> find_value(string): returns a (possibly empty) vector<string>
//                                       which is a list of all keys where val is located.
//    MVM(initializer_list<Element>): initialize the data_ member to the initializer_list.
//                                    is added in initializer_list order.
//    size_t size(): size of data_.
//    bool add(string, string): Should use find_keys. value is already in values_, do nothing but return false.
//                              The return is always true unless the key and the value (both) already exist.
//    bool remove_key(string): check if key is in the MVM (use find_key).
//    vector<string> remove_value(string): for every Element in the MVM.
//    friend ostream&operator << (ostream&, MVM&): print an MVM.
//
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>  // the head File
using std::lower_bound;  // C++ STL

#include <utility>  // the head File
using std::move;  // C++ STL

#include "functions.h"  // the head File

// Take a string key and an initializer_list values and construct an Element with those values.
Element::Element(string key, initializer_list<string> values) {
    key_ = move(key);  // get the key use the std::move
    values_ = values;  // get the value
}

// This will help with testing. You can see if two Elements are equal.
bool Element::operator == (const Element &element) const {
    return key_ == element.key_ and values_ == element.values_;
}

// output the Element to the provided ostream (do not just print to cout).
ostream& operator << (ostream & out, Element & element) {
    out << element.key_ << ":";

    // use the for loop one by one to cout
    for (auto i = 0; i < element.values_.size(); ++i) {
        out << element.values_[i];

        // in the end
        if (i == element.values_.size() - 1)
            break;
        out << ",";
    }
    return out;
}

// is added in initializer_list order.
MVM::MVM(initializer_list<Element> element) {
    data_ = element;  // get the element into the data_
}

vector<Element>::iterator MVM::find_key(string key) {
    auto itr = lower_bound(data_.begin(), data_.end(), key,
            [](Element element, string key){ return element.key_ < key;});  // must use the algorithm lower_bound.
    return itr;  // returns an iterator that points to an Element in data_.
}

vector<string> MVM::find_value(string value) {
    vector<string> v;

    // for loop the every element in data.
    for (const auto &element : data_)

        // if the value not in the value_
        if (find(element.values_.begin(), element.values_.end(), value) != element.values_.end())
            v.push_back(element.key_);
    return v;  // returns a (possibly empty) vector<string> which is a list of all keys where val is located.
}

// just the size
size_t MVM::size() {
    return data_.size();  // the data_ size
}

// print an MVM.
ostream& operator << (ostream & out, MVM & data) {

    // for loop the every element in data_
    for (auto i = 0; i < data.data_.size(); ++i) {
        out << data.data_[i];

        // if int the end
        if (i == data.data_.size() - 1)
            break;
        out << " ";
    }
    return out;
}

bool MVM::add(string key, string value) {
    Element element(key, {value});

    // Should use find_keys
    if (find_key(key)->key_ == key) {
        auto f = find(find_key(key)->values_.begin(), find_key(key)->values_.end(), value);

        // value is already in values_, do nothing but return false.
        if (f != find_key(key)->values_.end())
            return false;
        
        // push_back in every value
        find_key(key)->values_.push_back(value);
    } else  // not in the element
        data_.insert(find_key(key), element);

    // always return true
    return true;
}

// check if key is in the MVM (use find_key).
bool MVM::remove_key(string key) {

    // if yes, remove and return true.
    if (find_key(key)->key_ == key) {
        data_.erase(find_key(key));
        return true;
    }

    // if not do nothing and return false.
    return false;
}

// for every Element in the MVM.
vector<string> MVM::remove_value(string value) {

    // if the value is in the values_ of the Element, remove it.
    vector<string> v = find_value(value);

    // for loop in every key
    for (const auto &key : v)
        find_key(key)->values_.erase(find(find_key(key)->values_.begin(), find_key(key)->values_.end(), value));
    return v;  // return a vector<string> of all the keys where a value was removed.
}
