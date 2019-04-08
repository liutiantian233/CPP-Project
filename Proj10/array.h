#ifndef PROJECT10_ARRAY_H
#define PROJECT10_ARRAY_H

#include <iostream>
using std::cout; using std::endl; using std::boolalpha; using std::ostream;

#include <initializer_list>
using std::initializer_list;

#include <algorithm>
using std::max; using std::copy; using std::swap;

#include <utility>
using std::make_pair; using std::pair;

#include <stdexcept>
using std::runtime_error;

const static size_t element_array_size = 5;

template <typename K, typename V>
struct Element {

public:

    K key_;
    V values_[element_array_size];

    size_t count_ = 0;
    Element() = default;

    Element(K, initializer_list<V>);
    bool operator == (const Element&) const;
    bool operator < (const K&) const;

    friend ostream& operator << (ostream& oss, Element& element) {
        // Code for the ostream operator goes here
    }

};

// Code for Element functions goes here

template <typename K, typename V>
class MVM {

public:

    Element<K, V> * data_ = nullptr;
    size_t num_keys_ = 0;
    size_t num_elements_ = 0;

    Element<K, V> * find_key(K);
    size_t find_value(V, K*&);
    void grow();

public:

    MVM() = default;

    MVM(initializer_list<Element<K, V>>);
    MVM(const MVM&);
    ~MVM();
    size_t size();

    bool add(K, V);
    bool remove_key(K);
    size_t remove_value(V, K*&);
    friend ostream& operator << (ostream& oss, MVM& mvm) {
        // Code for the ostream operator goes here
    }

};

// Code for MVM functions goes here

#endif //PROJECT10_ARRAY_H
