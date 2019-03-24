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
