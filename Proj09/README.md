# MVM

## Assignment Overview

In this assignment you will practice creating a custom data structure, `MVM`, which extends the map class, without using the potential STL bases (map and set). You will create two classes to do this work.

## Background

You are going to create a container called a `Multi_Value_Map` but which we will shorten to just `MVM`. A `MVM` is a kind of associative container that has unique keys, like a regular map, but can have associated with each key a **group** of values, not just one value. That is, you store values that have a key: `{value_a, value_b, value_c, ...}` relationship. The `MVM` has the following restrictions:

- The key is unique. There is no repeat of a key in a `MVM`.
- The values associated with a **particular** key are also unique. A value cannot be repeated in association with a key. **However** a value can show up associated with **different** keys (can repeat across multiple keys) and that is allowed.
- The entries in a `MVM` are always sorted in key order. That is, if you add a new key to a `MVM`, it will be placed in its proper sorted position relative to the other keys. You do not need to use the sort function to do this, see details below.
- The values associated with a key are stored in first come, first serve order. That is, the first entry in a list of values associated with a key is the first value added, the second in the list the second value added.

You are going to build an `MVM` that stores keys as strings and values as string. No templating of your class yet. To support this work, we will also design another class called `Element`. You can think of `Element` as the payload class to be used by `MVM`. The organization will look something like the following:

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj09/Proj09-1.png)

Each `Element` has a `string key_` and a `vector<string> values_` (note the underlines trailing the data members). The `MVM` has a `vector<Element> data_` which is organized in key order. Note that the value `a` is repeated in multiple Element's `value_` vector but no value is repeated in the same `values_` vector. Neither is any `key_` repeated. The indicies of `data_` are shown for clarity and are not part of the actual data structure.

# Details

We provide a header file, which provides details of type for all the required methods and functions for the classes `Element` and `MVM`.

## `Element`

`Element() = default`

- Default. Do not need to write.

`Element(string key, initializer_list<string> values)`

- Take a string key and an initializer_list values and construct an `Element` with those values.

`bool operator == (const Element&)`

- Two `Elements` are equal if their two `keys_` are equal and if their two `values_` are equal.
  - return true if the two `Elements` meet this condition, false otherwise.
  - this is a member function.
  - Note: you do not have to compare each of the elements in `values_`, just compare the vectors directly.
- This will help with testing. You can see if two Elements are equal (what you think should be in the vector and what actually is). One liner, easy to write.

`friend ostream& operator << (ostream&, Element&)`

- output the `Element` to the provided ostream (do not just print to cout).

## `MVM`

`MVM() = default`

- Default. Do not need to write.

`MVM(initializer_list<Element>)`

- initialize the `data_` member to the `initializer_list`.
- is added in `initializer_list` order (see note below).

`vector<Element>::iterator find_key(string key);`

- must use the algorithm `std::lower_bound`.
- returns an iterator that points to an `Element` in `data_`.
- return value cases are:
  - points to an `Element` in `data_` which has the key.
  - point to an `Element` in `data_` which is just bigger than the key (thus the key is not there).
    - if `data_.end()`, the key is not there and it is bigger than all existing keys.

`vector<string> find_value(string val)`

- returns a (possibly empty) `vector<string>` which is a list of all keys where `val` is located.

`bool add(string key, string value)`

Should use `find_keys`. The cases are:

- The `key` exists. Check the `value`.
  - `value` not in `values_`, push it onto the back of `values_`.
  - `value` is already in `values_`, do nothing but return false.
- The `key` is not there and it is bigger than all existing keys.
  - push a new `Element(key, {value})` onto the back of `data_`.
- The `key` is not there. The `find_key` iterator can be used to do an `insert` into `data_`.
- The return is always true unless the key and the value (both) already exist.

`size_t size()`

- size of `data_`.

`bool remove_key(string key)`

- check if `key` is in the `MVM` (use `find_key`).
  - if yes, remove and return true.
  - if not do nothing and return false.

`vector<string> remove_value(string)`

- for every `Element` in the `MVM`.
  - if the `value` is in the `values_` of the `Element`, remove it.
  - return a `vector<string>` of all the keys where a value was removed.

`friend ostream& operator << (ostream&, MVM&)`

- print an `MVM`.
