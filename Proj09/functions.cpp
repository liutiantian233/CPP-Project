#include <algorithm>
using std::lower_bound;

#include <utility>
using std::move;

#include "functions.h"

Element::Element(string key, initializer_list<string> values) {
    key_ = move(key);
    values_ = values;
}

bool Element::operator == (const Element &element) const {
    return key_ == element.key_ and values_ == element.values_;
}

ostream& operator << (ostream & out, Element & element) {
    out << element.key_ << ":";
    for (auto i = 0; i < element.values_.size(); ++i) {
        out << element.values_[i];
        if (i == element.values_.size() - 1)
            break;
        out << ",";
    }
    return out;
}

MVM::MVM(initializer_list<Element> element) {
    data_ = element;
}

vector<Element>::iterator MVM::find_key(string key) {
    auto itr = lower_bound(data_.begin(), data_.end(), key,
            [](Element element, string key){ return element.key_ < key;});
    return itr;
}

vector<string> MVM::find_value(string value) {
    vector<string> v;
    for (const auto &element : data_)
        if (find(element.values_.begin(), element.values_.end(), value) != element.values_.end())
            v.push_back(element.key_);
    return v;
}

size_t MVM::size() {
    return data_.size();
}

ostream& operator << (ostream & out, MVM & data) {
    for (auto i = 0; i < data.data_.size(); ++i) {
        out << data.data_[i];
        if (i == data.data_.size() - 1)
            break;
        out << " ";
    }
    return out;
}

bool MVM::add(string key, string value) {
    Element element(key, {value});
    if (find_key(key)->key_ == key) {
        auto f = find(find_key(key)->values_.begin(), find_key(key)->values_.end(), value);
        if (f != find_key(key)->values_.end())
            return false;
        find_key(key)->values_.push_back(value);
    } else
        data_.insert(find_key(key), element);
    return true;
}

bool MVM::remove_key(string key) {
    if (find_key(key)->key_ == key) {
        data_.erase(find_key(key));
        return true;
    }
    return false;
}

vector<string> MVM::remove_value(string value) {
    vector<string> v = find_value(value);
    for (const auto &key : v)
        find_key(key)->values_.erase(find(find_key(key)->values_.begin(), find_key(key)->values_.end(), value));
    return v;
}
