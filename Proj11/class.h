#ifndef PROJECT11_CLASS_H
#define PROJECT11_CLASS_H

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
    Element* next_ = nullptr;

    // Optional
    // Element* previous = nullptr;

    size_t count_ = 0;

    Element() = default;
    Element(K key, initializer_list<V> values);
    Element(const Element& other);
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
    Element<K, V> * data_head_ = nullptr;

    // Optional
    // Element<K, V> * data_tail_ = nullptr;
    // size_t num_elements_ = 0;

    size_t num_keys_ = 0;

    pair<Element<K, V>*, Element<K, V>*> find_key(K key);
    MVM find_value(V value);

public:
    // Constructors
    MVM() = default;
    MVM(initializer_list<pair<K, initializer_list<V>>>);

    // Rule of Three
    MVM(const MVM& other);
    MVM& operator = (const MVM& other);
    ~MVM();

    // Other Functions
    size_t size();
    bool add(K key, V value);
    bool remove_key(K key);
    MVM remove_value(V value);

    friend ostream& operator << (ostream& oss, MVM& mvm) {
        // Code for the ostream operator goes here
    }
};

// Code for MVM functions goes here

#endif //PROJECT11_CLASS_H
