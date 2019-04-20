////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #11   MVM List
//
//  Define the head File "iostream" "initializer_list" "algorithm" "utility" "stdexcept"
//    use the C++ Standard Library headers
//    the "algorithm" "utility" "stdexcept" "initializer_list" are C++ tools
//
//  Defining class public function in Element:
//    Element(K key, initializer_list<V> values): copy into the array values_ and set count_ correctly.
//                                                Sets next_ to nullptr (no next Element in a list yet).
//    bool operator == (const Element&): Behavior is identical to the previous project.
//                                       Doesn't need to account for next_.
//    friend ostream& operator << (ostream&, Element&): Behavior is identical to the previous project.
//    bool operator < (const K&): compares the key passed to the element's key.
//    Element(const Element& other): Copy ctor. Copies count_ and values_. Sets next_ to nullptr.
//                                   Remember that values_ is a fixed-size array.
//                                   You know how to copy that, you just did it in project 10.
//
//  Defining class public function in MVM:
//    MVM(initializer_list<Element<K, V>): Behavior is identical to the previous project. However,
//                                         you are now adding Elements, in order as found in the initializer_list,
//                                         into a linked list. Same idea, different data structure.
//    pair<Element*, Element*> find_key(K key): We can no longer use lower_bound as we mentioned.
//    However, having a singly linked list means that finding only the first greater value is of limited use.
//    MVM find_value(V value): creates an MVM where each key is a key that has value in its values_,
//                             and the only value associated with each key is value.
//    size_t size(): Returns num_keys_.
//    bool add(string key, string value): Behavior is identical to previous project,
//                                        with the exception being that you no longer need to call grow(),
//                                        just dynamically allocate a new Element as necessary.
//    bool remove_key(K key): Behavior is identical to previous project.
//    MVM remove_value(V value): creates and returns a MVM of the same format used in find_value.
//    friend ostream& operator << (ostream&, MVM&): print an MVM.
//    ~MVM(): Destructor. Deletes any allocated memory as necessary.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PROJECT11_CLASS_H
#define PROJECT11_CLASS_H

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

template <typename K, typename V>
// the struct about Element
struct Element {

public:
    K key_;
    V values_[element_array_size];
    Element * next_ = nullptr;

    // Optional
    // Element * previous = nullptr;

    size_t count_ = 0;

    Element() = default;
    Element(K key, initializer_list<V> values);
    Element(const Element& other);
    bool operator == (const Element&) const;
    bool operator < (const K&) const;

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
    // copy into the array values_ and set count_ correctly.
    key_ = key;
    if (values.size() <= element_array_size) {
        count_ = values.size();
        copy(values.begin(), values.end(), values_);
        next_ = nullptr;
    }
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
Element<K, V>::Element(const Element &other) {
    // Copy ctor. Copies count_ and values_. Sets next_ to nullptr.
    // Remember that values_ is a fixed-size array. You know how to copy that, you just did it in project 10.
    key_ = other.key_;
    count_ = other.count_;
    copy(other.values_, other.values_ + other.count_, values_);
    next_ = nullptr;
}

template <typename K, typename V>
bool Element<K, V>::operator < (const K &key) const {
    return key_ < key;  // return the bigger key
}





template <typename K, typename V>
class MVM {

public:
    Element<K, V> * data_head_ = nullptr;

    // Optional
    Element<K, V> * data_tail_ = nullptr;
    // size_t num_elements_ = 0;

    size_t num_keys_ = 0;

    pair<Element<K, V>*, Element<K, V>*> find_key(K key);
    MVM<K, V> find_value(V value);

public:
    // Constructors
    MVM() = default;
    MVM(initializer_list<Element<K, V>>);

    // Rule of Three
    MVM(const MVM& other);
    MVM<K, V>& operator = (const MVM& other);
    ~MVM();

    // Other Functions
    size_t size();
    bool add(K key, V value);
    bool remove_key(K key);
    MVM<K, V> remove_value(V value);

    friend ostream& operator << (ostream& oss, MVM& mvm) {
        // Code for the ostream operator goes here
        for (auto i = 0; i < mvm.size(); ++i) {
            oss << *mvm.data_head_;
            if (i == mvm.size() - 1)
                break;
            oss << " ";
            mvm.data_head_ = mvm.data_head_->next_;
        }
        return oss;
    }
};

// Code for MVM functions goes here
template <typename K, typename V>
MVM<K, V>::MVM(const MVM &other) {
    num_keys_ = other.num_keys_;
    // if the data_head_ not nullptr, need to delete
    if (data_head_ != nullptr) {
        auto * point = data_head_;  // make a point to data_head_
        num_keys_ = 0;

        // while loop to get all point
        while (point != nullptr) {
            data_head_ = data_head_->next_;
            delete point;  // delete the point
            point = data_head_;
        }
        data_head_ = nullptr;
        data_tail_ = nullptr;
    }
    
    // if other.data_head_ not nullptr, need the copy
    if (other.data_head_ != nullptr) {
        data_head_ = new Element<K,V> (*(other.data_head_));
        
        // make the point to data_head_ and other.data_head_
        auto * point1 = data_head_;
        auto * point2 = other.data_head_;
        data_tail_ = point1;
        
        // while loop to get other.data_head_ next.
        while (point2->next_ != nullptr) {
            data_tail_ = point1;
            point1 = new Element<K,V> (*(point2->next_));
            data_tail_->next_ = point1;
            point2 = point2->next_;
        }
        data_tail_ = point1;
    } else {
        
        // data_head_ and data_tail_ is nullptr
        data_head_ = nullptr;
        data_tail_ = nullptr;
    }
}

template <typename K, typename V>
MVM<K, V>& MVM<K, V>::operator = (const MVM &other) {
    // Makes this have the same values as other.
    MVM<K, V> mvm(other);
    num_keys_ = mvm.num_keys_;
    //use the copy ctor to make a copy of other that you can then use to swap data members with the local MVM.
    swap(data_head_, mvm.data_head_);
    swap(data_tail_, mvm.data_tail_);
    return mvm;
}

template <typename K, typename V>
size_t MVM<K, V>::size() {
    // Returns num_keys_.
    return num_keys_;
}

template <typename K, typename V>
MVM<K, V>::MVM(initializer_list<Element<K, V>> element) {
    // Behavior is identical to the previous project.
    if (element.size() != 0)
        data_head_ = new Element<K, V> (*element.begin());

    // make a point to data_head_
    auto * point = data_head_;

    // for loop to add the element
    for (auto i = 1; i < element.size(); ++i) {
        data_tail_ = new Element<K, V> (*(element.begin() + i));
        point->next_ = data_tail_;
        point = point->next_;
    }
    num_keys_ = element.size();
}

template <typename K, typename V>
MVM<K, V>::~MVM() {
    // Destructor. Deletes any allocated memory as necessary.
    auto * point = data_head_;  // make a point to data_head_
    num_keys_ = 0;

    // while loop to get all point
    while (point != nullptr) {
        data_head_ = data_head_->next_;
        delete point;  // delete the point
        point = data_head_;
    }
    data_head_ = nullptr;
    data_tail_ = nullptr;
}

template <typename K, typename V>
pair<Element<K, V>*, Element<K, V>*> MVM<K, V>::find_key(K key) {
    // We can no longer use lower_bound as we mentioned.

    // the .first points to the Element just behind (just previous to) the Element pointed to by .second
    Element<K, V> * first = nullptr;

    // the .second points to the Element whose key_ is either equal to or just greater than the parameter key.
    Element<K, V> * second = data_head_;
    if (second == nullptr)  // if the empty
        return pair<Element<K, V>*, Element<K, V>*> (first, second);
    while (second->key_ < key) {
        first = second;
        second = second->next_;
        if (second == nullptr)
            break;
    }
    return pair<Element<K, V>*, Element<K, V>*> (first, second);
}

template <typename K, typename V>
MVM<K, V> MVM<K, V>::find_value(V value) {
    // finds all keys where value is located.
    MVM<K, V> mvm;
    // creates an MVM where each key is a key that has value in its values_
    // and the only value associated with each key is value.
    for (auto * point = data_head_; point != nullptr; point = point->next_)
        for (auto item = 0; item < point->count_; ++item)
            if (point->values_[item] == value)
                mvm.add(point->key_, value);
    // returns the new MVM.
    return mvm;
}

template <typename K, typename V>
bool MVM<K, V>::add(K key, V value) {
    // Behavior is identical to previous project
    // with the exception being that you no longer need to call grow()
    // just dynamically allocate a new Element as necessary.
    auto found = find_key(key);

    // if the second can to find
    if (found.second != nullptr and found.second->key_ == key) {
        // to find the value
        auto f = std::find(found.second->values_, found.second->values_ + found.second->count_, value);
        if (f != found.second->values_ + found.second->count_ or found.second->count_ == element_array_size)
            return false;
        found.second->values_[found.second->count_++] = value;
    } else {
        auto data = new Element<K, V> (key, {value});

        // if the found is empty
        if (found.first == nullptr and found.second == nullptr)
            data_head_ = data;
        // if the found is first
        if (found.first == nullptr and found.second != nullptr) {
            data_head_ = data;
            data_head_->next_ = found.second;
        }
        // if the found is end
        if (found.first != nullptr and found.second == nullptr) {
            found.first->next_ = data;
        }
        // if the found is middle
        if (found.first != nullptr and found.second != nullptr) {
            found.first->next_ = data;
            found.first->next_->next_ = found.second;
        }
        num_keys_ += 1;
    }
    return true;
}

template <typename K, typename V>
bool MVM<K, V>::remove_key(K key) {
    // Behavior is identical to previous project.
    auto found = find_key(key);

    // use the find_key
    if (found.second->key_ == key) {
        num_keys_ -= 1;
        // if the found.first is nullptr
        if (found.first == nullptr)
            data_head_ = found.second->next_;
        else
            found.first->next_ = found.second->next_;
        delete found.second;  // delete the second
        return true;
    }
    return false;
}

template <typename K, typename V>
MVM<K, V> MVM<K, V>::remove_value(V value) {
    // finds all keys where value is located, and removes value from the values_ array.
    auto * point1 = data_head_;
    auto mvm = find_value(value);  // use the find_value function to handle most of the work.
    // creates and returns a MVM of the same format used in find_value.
    auto * point2 = mvm.data_head_;
    for (auto i = 0; i < num_keys_; ++i) {
        if (point2 == nullptr)
            break;
        
        // if point1->key_ same with point2->key_
        if (point1->key_ == point2->key_) {
            for (auto j = 0; j < point1->count_; ++j) {
                if (point1->values_[j] == value) {
                    std::rotate(point1->values_ + j, point1->values_ + j + 1, point1->values_ + point1->count_);
                    point1->count_ -= 1;
                }
            }
            point2 = point2->next_;
        }
        point1 = point1->next_;
    }
    return mvm;
}

#endif //PROJECT11_CLASS_H
