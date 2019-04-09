# MVM Array

## Assignment Overview

In the previous assignment you were introduced to a custom data structure, `MVM`, that did not use the potential STL bases (map and set) but used the vector class. In this project, you will re-write the `MVM` as a templated class without the use of vector by using static and dynamic arrays.

## Background

You are going to re-create the `MVM` with templating and without the use of the vector class. To do so, you will use templated dynamic and static arrays. The vector in the Element class will be replaced with a static array, and the vector in the `MVM` class will be replaced with a dynamic array. This means that only so many values can be associated with each key, but we can still accommodate a variable number of keys. Other than this one change, the basic properties of how the `MVM` class behaves remain the same. The implementation of the `MVM` will be different to handle the templating and lack of vectors.

## Templating

Both the Element class and the MVM class will have two templates. The type of keys will be referred to as `K`, and the type of values will be referred to as `V`.

## Element

Each `Element` has a `K key_` and a `V values_[element_array_size]`, as well as a new `size_t count_` to track the number of values currently being stored. The value `element_array_size` is a const global variable. Thus the size of the array in every `Element` will be the same and will be **fixed** for the duration of the program. It is not required to grow, and we will not test any `values_` array beyond this fixed size.

## MVM

The `MVM` has a `Element<K, V> * data_` which points to a dynamic array organized in key order, as well as a `size_t num_keys_` to keep track of the number of `Elements` presently in `data_`, and a `size_t num_elements_` to keep track of the total size of `Elements` that can be placed in the present `data_`. The `data_` array is **dynamic** and must grow as more Elements are added to it.

# Details

We provide a header file, `array.h`, which provides details of type for all the required methods and functions for the classes `Element` and `MVM`. In order to make the process of templating easier, you will write the function definitions in the same header file.

Remember, everything is public, not because it is a good idea but because it is easier to test your code that way.

# Element<K, V>

## Member functions re-used from project 09:

`Element() = default`

- Default ctor. Do not need to write.

`Element(K key, initializer_list<V> values)`

- Instead of copying into the vector, copy into the array `values_` and set `count_` correctly. The number of elements being copied will never exceed the fixed size of `values_`.

`bool operator == (const Element&) const`

- Behavior is identical to the previous project. Must properly set up `count_`.

`friend ostream& operator << (ostream& oss, Element& element)`

- Behavior is identical to the previous project.

## New member functions for project 10:

`bool operator < (const K&) const`

- Optional; compares the key passed to an `Elements` key; done correctly, allows easier use of the `lower_bound` algorithm.

# MVM<K, V>

## Member functions re-used from project 09:

`MVM() = default`

- Default ctor. Do not need to write.
