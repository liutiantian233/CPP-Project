////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #10   MVM Array
//
//  Define the head File "algorithm" "utility" "stdexcept" "initializer_list"
//    use the C++ Standard Library headers
//    the "algorithm" "utility" "stdexcept" "initializer_list" are C++ tools
//
//  Defining class public function in Element:
//    Element(K key, initializer_list<V> values): Instead of copying into the vector, copy into
//                                                the array values_ and set count_ correctly.
//                                                The number of elements being copied will never
//                                                exceed the fixed size of values_.
//    bool operator == (const Element&) const: Behavior is identical to the previous project.
//                                             Must properly set up count_.
//    friend ostream& operator << (ostream& oss, Element& element): Behavior is identical to the previous project.
//    bool operator < (const K&) const: compares the key passed to an Elements key; done correctly,
//                                      allows easier use of the lower_bound algorithm.
//
//  Defining class public function in MVM:
//    MVM(initializer_list<Element<K, V>>): Behavior is identical to the previous project. Must properly
//                                          allocate data_, and initialize num_keys_ and num_elements_.
//    Element<K, V> * find_key(K key): Behavior is identical to previous project but returns a pointer
//                                     (not an iterator) to an Element (or one past the last Element if not found)
//    size_t find_value(V values, K* (&keys_found)): We pass a values to search for and an array reference keys_found
//                                                   (note the odd parentheses). The intent is to fill the array
//                                                   keys_found with all keys containing the values.
//    size_t size(): Returns num_keys_.
//    bool add(string key, string value): Behavior is identical to previous project, with the following exception.
//    bool remove_key(K key): Behavior is identical to previous project.
//    size_t remove_value(V value, K* (&keys_found)): finds all keys where value is located,
//                                                    and removes value from the values_ array.
//    friend ostream& operator << (ostream& oss, MVM& mvm): print an MVM.
//    ~MVM(): Destructor. Deletes any allocated memory as necessary.
//    void grow(): If the array is empty (i.e. num_elements_ is 0 and data_ is a nullptr) set the num_elements_ to
//                 2 and dynamically allocate data_ to be of size 2.
//                 Otherwise, reallocate data_ with twice as many num_elements_ and the correct keys stored
//                 internally, taking care to manage the dynamically allocated memory correctly.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PROJECT10_ARRAY_H
#define PROJECT10_ARRAY_H

#include <iostream>  // the head File
using std::cout; using std::endl; using std::boolalpha; using std::ostream;  // C++ STL

#include <initializer_list>  // the head File
using std::initializer_list;  // C++ STL

#include <algorithm>  // the head File
using std::max; using std::copy; using std::swap;  // C++ STL

#include <utility>  // the head File
using std::make_pair; using std::pair;  // C++ STL

#include <stdexcept>  // the head File
using std::runtime_error;  // C++ STL

// the const about the size
const static size_t element_array_size = 5;

// use the template class
template <typename K, typename V>
struct Element {

public:

    K key_;
    V values_[element_array_size];
    size_t count_ = 0;
    
    Element() = default;
    Element(K key, initializer_list<V> values);
    bool operator == (const Element&) const;
    bool operator < (const K&) const;

    // friend function to print the element
    friend ostream& operator << (ostream& oss, Element& element) {
        // Code for the ostream operator goes here
        oss << element.key_ << ":";
        for (auto i = 0; i < element.count_; ++i) {
            oss << element.values_[i];
            if (i == element.count_ - 1)
                break;
            oss << ",";
        }
        return oss;
    }

};

// Code for Element functions goes here
template <typename K, typename V>
Element<K, V>::Element(K key, initializer_list<V> values) {

    // Default constructor
    key_ = key;
    count_ = values.size();
    copy(values.begin(), values.end(), std::begin(values_));
}

template <typename K, typename V>
bool Element<K, V>::operator == (const Element &element) const {

    // if key is element and count
    if (key_ == element.key_ and count_ == element.count_) {
        for (auto i = 0; i < count_; ++i)
            
            if (values_[i] != element.values_[i])
                return false;
        return true;
    }
    // if not equal
    return false;
}

template <typename K, typename V>
bool Element<K, V>::operator < (const K &key) const {
    return key_ < key;  // the predicate
}

// use the template class
template <typename K, typename V>
class MVM {

public:

    // Define all parameters and variables
    Element<K, V> * data_ = nullptr;
    size_t num_keys_ = 0;
    size_t num_elements_ = 0;

    Element<K, V> * find_key(K key);
    size_t find_value(V values, K* (&keys_found));
    void grow();

public:

    // Define all functions
    MVM() = default;
    MVM(initializer_list<Element<K, V>>);
    ~MVM();
    size_t size();
    bool add(K, V);
    bool remove_key(K key);
    size_t remove_value(V value, K* (&keys_found));

    // friend function to print the element
    friend ostream& operator << (ostream& oss, MVM& mvm) {
        // Code for the ostream operator goes here
        for (auto i = 0; i < mvm.size(); ++i) {
            oss << mvm.data_[i];
            if (i == mvm.size() - 1)
                break;
            oss << " ";
        }
        return oss;
    }

};

// Code for MVM functions goes here
template <typename K, typename V>
MVM<K, V>::MVM(initializer_list<Element<K, V>> element) {

    // Construct default parameters and variables
    data_ = new Element<K, V> [element.size()];
    num_keys_ = element.size();
    num_elements_ = element.size();

    // use the copy
    copy(element.begin(), element.end(), data_);
}

template <typename K, typename V>
MVM<K, V>::~MVM() {
    // Destructor. Deletes any allocated memory as necessary.
    delete [] data_;  // delete the data
}

template <typename K, typename V>
size_t MVM<K, V>::size() {
    return num_keys_;  // find the num keys
}

template <typename K, typename V>
Element<K, V>* MVM<K, V>::find_key(K key) {

    // use the lower_bound to find point
    auto point = std::lower_bound(data_, data_ + num_keys_, key);
    return point;
}

template <typename K, typename V>
size_t MVM<K, V>::find_value(V values, K* (&keys_found)) {
    size_t count = 0, result = 0;
    if (keys_found == nullptr) {

        // the for loop in the MVM
        for (auto i = 0; i < num_keys_; ++i)

            // use the find
            if (std::find(data_[i].values_, data_[i].values_ + data_[i].count_, values)
            != data_[i].values_ + data_[i].count_)
                count += 1;
    } else  // If keys_found is not a nullptr, throws a runtime_error.
        throw runtime_error("NOT NULL");

    // finds all keys where values is located.
    if (count != 0 and result < count) {
        keys_found = new K [count];
        for (auto i = 0; i < num_keys_; ++i)
            for (auto j = 0; j < data_[i].count_; ++j)

                if (data_[i].values_[j] == values)
                    // creates a dynamic array pointed to by keys_found that holds
                    // the keys that have values in their values_ array.
                    keys_found[result++] = data_[i].key_;
    }
    return count;
}

template <typename K, typename V>
void MVM<K, V>::grow() {

    // If the array is empty (i.e. num_elements_ is 0 and data_ is a nullptr)
    // set the num_elements_ to 2 and dynamically allocate data_ to be of size 2.
    if (num_elements_ == 0 and data_ == nullptr) {
        num_elements_ = 2;
        data_ = new Element<K, V> [2];
    } else {
        // Otherwise, reallocate data_ with twice as many num_elements_ and the correct keys
        // stored internally, taking care to manage the dynamically allocated memory correctly.
        num_elements_ *= 2;
        auto * new_data = new Element<K, V> [num_elements_];
        copy(data_, data_ + num_keys_, new_data);
        swap(data_, new_data);
        delete [] new_data;
    }
}

template <typename K, typename V>
bool MVM<K, V>::add(K key, V value) {

    // Behavior is identical to previous project, with the following exception
    Element<K, V> element(key, {value});
    if (find_key(key) != data_ + num_elements_) {
        if (find_key(key)->key_ == key) {
            auto f = std::find(find_key(key)->values_, find_key(key)->values_ + find_key(key)->count_, value);

            if (f != find_key(key)->values_ + find_key(key)->count_ or find_key(key)->count_ == element_array_size)
                return false;
            find_key(key)->values_[find_key(key)->count_++] = value;
        } else {
            if (num_keys_ == num_elements_)
                grow();
            data_[num_keys_++] = element;
            std::rotate(find_key(key), data_ + num_keys_ - 1, data_ + num_keys_);
        }
    } else {

        // If you are adding a new key to the MVM, and the dynamic array is full (i.e. num_keys_ == num_elements_)
        // you need to call the grow() function to make data_ bigger.
        if (num_keys_ == num_elements_)
            grow();
        data_[num_keys_++] = element;
    }
    return true;
}

template <typename K, typename V>
bool MVM<K, V>::remove_key(K key) {

    // Behavior is identical to previous project.
    if (find_key(key) != data_ + num_elements_) {
        if (find_key(key)->key_ == key) {
            std::rotate(find_key(key), find_key(key) + 1, data_ + num_keys_);
            num_keys_ -= 1;
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
size_t MVM<K, V>::remove_value(V value, K* (&keys_found)) {
    size_t count = 0, result = 0;

    // finds all keys where value is located, and removes value from the values_ array.
    if (keys_found == nullptr) {
        for (auto i = 0; i < num_keys_; ++i)
            // use the find function to handle most of the work.
            
            if (std::find(data_[i].values_, data_[i].values_ + data_[i].count_, value)
            != data_[i].values_ + data_[i].count_)
                count += 1;
    } else
        // Like before, if keys_found is not a nullptr, throws a runtime_error.
        throw runtime_error("NOT NULL");
    
    if (count != 0 and result < count) {
        keys_found = new K [count];
        for (auto i = 0; i < num_keys_; ++i)
            for (auto j = 0; j < data_[i].count_; ++j)
                if (data_[i].values_[j] == value) {

                    std::rotate(data_[i].values_ + j + 1, data_[i].values_ + j + 2, data_[i].values_ + data_[i].count_);
                    data_[i].count_ -= 1;
                    // creates a dynamic array pointed to by keys_found that
                    // holds the keys that had value in their values_ array.
                    keys_found[result++] = data_[i].key_;
                }
    }

    // returns the size of the array pointed to by keys_found.
    return count;
}

#endif //PROJECT10_ARRAY_H
