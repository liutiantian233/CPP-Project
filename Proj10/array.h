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
    Element(K key, initializer_list<V> values);
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
    key_ = key;
    count_ = values.size();
    copy(values.begin(), values.end(), std::begin(values_));
}

template <typename K, typename V>
bool Element<K, V>::operator == (const Element &element) const {
    if (key_ == element.key_ and count_ == element.count_) {
        for (auto i = 0; i < count_; ++i)
            if (values_[i] != element.values_[i])
                return false;
        return true;
    }
    return false;
}

template <typename K, typename V>
bool Element<K, V>::operator < (const K &key) const {
    return key_ < key;
}

template <typename K, typename V>
class MVM {

public:

    Element<K, V> * data_ = nullptr;
    size_t num_keys_ = 0;
    size_t num_elements_ = 0;

    Element<K, V> * find_key(K key);
    size_t find_value(V values, K* (&keys_found));
    void grow();

public:

    MVM() = default;
    MVM(initializer_list<Element<K, V>>);
    MVM(const MVM& other);
    ~MVM();
    size_t size();
    bool add(K, V);
    bool remove_key(K key);
    size_t remove_value(V value, K* (&keys_found));

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
    data_ = new Element<K, V> [element.size()];
    num_keys_ = element.size();
    num_elements_ = element.size();
    copy(element.begin(), element.end(), data_);
}

template <typename K, typename V>
MVM<K, V>::~MVM() {
    delete [] data_;
}

template <typename K, typename V>
size_t MVM<K, V>::size() {
    return num_keys_;
}

template <typename K, typename V>
Element<K, V>* MVM<K, V>::find_key(K key) {
    auto point = std::lower_bound(data_, data_ + num_keys_, key);
    return point;
}

template <typename K, typename V>
size_t MVM<K, V>::find_value(V values, K* (&keys_found)) {
    size_t count = 0, result = 0;
    if (keys_found == nullptr) {
        for (auto i = 0; i < num_keys_; ++i)
            if (std::find(data_[i].values_, data_[i].values_ + data_[i].count_, values)
            != data_[i].values_ + data_[i].count_)
                count += 1;
    } else
        throw runtime_error("NOT NULL");
    if (count != 0 and result < count) {
        keys_found = new K [count];
        for (auto i = 0; i < num_keys_; ++i)
            for (auto j = 0; j < data_[i].count_; ++j)
                if (data_[i].values_[j] == values)
                    keys_found[result++] = data_[i].key_;
    }
    return count;
}

template <typename K, typename V>
void MVM<K, V>::grow() {
    if (num_elements_ == 0 and data_ == nullptr) {
        num_elements_ = 2;
        data_ = new Element<K, V> [2];
    } else {
        num_elements_ *= 2;
        auto * new_data = new Element<K, V> [num_elements_];
        copy(data_, data_ + num_keys_, new_data);
        swap(data_, new_data);
        delete [] new_data;
    }
}

template <typename K, typename V>
bool MVM<K, V>::add(K key, V value) {
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
        if (num_keys_ == num_elements_)
            grow();
        data_[num_keys_++] = element;
    }
    return true;
}

template <typename K, typename V>
MVM<K, V>::MVM(const MVM &other) {
    other = new initializer_list<Element<K, V>> [num_elements_];
    copy(data_, data_ + num_elements_, other);
}

template <typename K, typename V>
bool MVM<K, V>::remove_key(K key) {
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
    if (keys_found == nullptr) {
        for (auto i = 0; i < num_keys_; ++i)
            if (std::find(data_[i].values_, data_[i].values_ + data_[i].count_, value)
            != data_[i].values_ + data_[i].count_)
                count += 1;
    } else
        throw runtime_error("NOT NULL");
    if (count != 0 and result < count) {
        keys_found = new K [count];
        for (auto i = 0; i < num_keys_; ++i)
            for (auto j = 0; j < data_[i].count_; ++j)
                if (data_[i].values_[j] == value) {
                    std::rotate(data_[i].values_ + j + 1, data_[i].values_ + j + 2, data_[i].values_ + data_[i].count_);
                    data_[i].count_ -= 1;
                    keys_found[result++] = data_[i].key_;
                }
    }
    return count;
}

#endif //PROJECT10_ARRAY_H
