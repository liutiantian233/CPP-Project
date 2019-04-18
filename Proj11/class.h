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
    copy(values.begin(), values.end(), values_);
    next_ = nullptr;
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
    key_ = other.key_;
    count_ = other.count_;
    copy(other.values_, other.values_ + other.count_, values_);
    Element* next_ = nullptr;
}

template <typename K, typename V>
bool Element<K, V>::operator < (const K &key) const {
    return key_ < key;
}

template <typename K, typename V>
class MVM {

public:
    Element<K, V> * data_head_ = nullptr;

    // Optional
    // Element<K, V> * data_tail_ = nullptr;
    // size_t num_elements_ = 0;

    size_t num_keys_ = 0;

    pair<Element<K, V>*, Element<K, V>*> find_key(K key);
    MVM<K, V> find_value(V value);

public:
    // Constructors
    MVM() = default;
    MVM(initializer_list<Element<K, V>>);

    // Rule of Three
    // MVM(const MVM& other);
    // MVM& operator = (const MVM& other);
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
size_t MVM<K, V>::size() {
    return num_keys_;
}

template <typename K, typename V>
MVM<K, V>::MVM(initializer_list<Element<K, V>> element) {
    data_head_ = new Element<K, V> (*element.begin());
    auto * point = data_head_;
    for (auto i = 1; i < element.size(); ++i) {
        point->next_ = new Element<K, V> (*(element.begin() + i));
        point = point->next_;
    }
    num_keys_ = element.size();
}

template <typename K, typename V>
MVM<K, V>::~MVM() {
    delete data_head_;
}

template <typename K, typename V>
pair<Element<K, V>*, Element<K, V>*> MVM<K, V>::find_key(K key) {
    Element<K, V> * first = nullptr;
    Element<K, V> * second = nullptr;
    auto * point = data_head_;
    for (auto i = 0; i < num_keys_; ++i) {
        if (point->key_ < key) {
            first = point;
            point = point->next_;
        } else {
            second = point;
            break;
        }
    }
    pair<Element<K, V>*, Element<K, V>*> pair1 (first, second);
    return pair1;
}

template <typename K, typename V>
MVM<K, V> MVM<K, V>::find_value(V value) {
    MVM<K, V> mvm;
    auto * point = data_head_;
    for (auto i = 0; i < num_keys_; ++i) {
        for (auto j = 0; j < point->count_; ++j) {
            if (point->values_[j] == value) {
                mvm.num_keys_ += 1;
                auto * point1 = new Element<K, V> (point->key_, {value});
                if (mvm.data_head_ == nullptr)
                    mvm.data_head_ = point1;
                else {
                    auto * point2 = mvm.data_head_;
                    while (point2->next_ != nullptr)
                        point2 = point2->next_;
                    point2->next_ = point1;
                }
            }
        }
        point = point->next_;
    }
    return mvm;
}

template <typename K, typename V>
bool MVM<K, V>::add(K key, V value) {
    Element<K, V> element(key, {value});
    if (find_key(key).first == nullptr and find_key(key).second == nullptr) {
        data_head_ = new Element<K, V> (element);
        num_keys_ += 1;
    }
    if (find_key(key).first == nullptr and find_key(key).second != nullptr) {
        if (find_key(key).second->key_ == key) {
            auto f = std::find(find_key(key).second->values_,
                               find_key(key).second->values_ + find_key(key).second->count_, value);
            if (f != find_key(key).second->values_ + find_key(key).second->count_
            or find_key(key).second->count_ == element_array_size)
                return false;
            data_head_->values_[data_head_->count_] = value;
            data_head_->count_ += 1;
        } else {
            num_keys_ += 1;
            auto * point = new Element<K, V> (element);
            point->next_ = data_head_;
            data_head_ = point;
        }
    }
    if (find_key(key).first != nullptr and find_key(key).second == nullptr) {
        num_keys_ += 1;
        auto * point1 = new Element<K, V> (element);
        auto * point2 = data_head_;
        while (point2->next_ != nullptr)
            point2 = point2->next_;
        point2->next_ = point1;
    }
    if (find_key(key).first != nullptr and find_key(key).second != nullptr) {
        if (find_key(key).second->key_ == key) {
            auto f = std::find(find_key(key).second->values_,
                               find_key(key).second->values_ + find_key(key).second->count_, value);
            if (f != find_key(key).second->values_ + find_key(key).second->count_
            or find_key(key).second->count_ == element_array_size)
                return false;
            auto * point = data_head_;
            while (point->key_ != key)
                point = point->next_;
            point->values_[point->count_] = value;
            point->count_ += 1;
        } else {
            num_keys_ += 1;
            auto * point1 = data_head_;
            auto * point2 = new Element<K, V>;
            auto * point0 = new Element<K, V> (element);
            while (key > point1->key_) {
                point2 = point1;
                point1 = point1->next_;
            }
            point2->next_ = point0;
            point0->next_ = point1;
        }
    }
    return true;
}

template <typename K, typename V>
bool MVM<K, V>::remove_key(K key) {
    if (find_key(key).second->key_ == key) {
        num_keys_ -= 1;
        if (data_head_->key_ == key)
            data_head_ = data_head_->next_;
        else {
            while (data_head_->next_->key_ != key)
                data_head_ = data_head_->next_;
            if (data_head_->next_->key_ == key)
                data_head_->next_ = data_head_->next_->next_;
        }
        return true;
    }
    return false;
}

template <typename K, typename V>
MVM<K, V> MVM<K, V>::remove_value(V value) {
    auto * point1 = data_head_;
    auto mvm = find_value(value);
    auto * point2 = mvm.data_head_;
    for (auto i = 0; i < num_keys_; ++i) {
        if (point2 == nullptr)
            break;
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
