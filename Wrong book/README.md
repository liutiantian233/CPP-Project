# `friend` designation

**True**

- it is a push, not a pull
- it indicates permission to access private class elements
- it can apply to both a class and a function

# difference `capacity` and `size` in vector

**size** is how many elements are in the vector

**capacity** is how many it **could** hold before growing

# `cin.ignore` method

**True**

- removes characters from the input stream

**False**

- ignores the last cin operation
- clears any errors, resets cin to be good
- closes the cin stream

# C++ `map` STL container

**False**

- it is a sequence
- it consists **only** of a series of keys
- requires a single template type to make a variable of type `map`

# special variable `this`

**True**

- it is automatically set by C++ to the address of the calling variable
- it is a pointer type

**False**

- you can **directly** assign it a new value in a class method
- it is an integer type
- must set it to use it in a class method

# random numbers

**True**

- they generate the same sequence when starting from the same seed
- when used in conjunction with a distribution, the distribution uses the random number generator as an argument
- C++ has multiple versions of random number generators

# operator *

**True**

- as a binary operation it represents multiply
- in a declaration it represents a pointer type
- as a unary operation it represents dereference
- in the expression `1 * 2` it represents multiplication

**False**

- in the declaration `long* p` it represents dereferencing of a pointer
- in `cout << *p`, the * represents the creation of a pointer variable `p`

# designation on constructor ( = default)

**True**

- for the default constructor, use the synthesized constructor

**False**

- over-rides **all** user provided constructors to use only the synthesized constructor
- sets the permissions of private data members to public

# `lambda` function

**True**

- it is a nameless function
- they are often used in conjunction with STL algorithms
- they have a capture list
- it is a function and can be invoked like a function

**False**

- it has a name
- it can not be used in a generic algorithm

# about C++ constructors

**True**

- they have the same name as the struct in which they are contained
- they can be overloaded for different parameter lists

**False**

- they return the newly made element of the struct type
- they can not take any arguments
- they can not be defined inside of a `struct`
- they require a `return` statement to return newly made `struct` type

# templated function

**True**

- it is itself not a function, but a way to create a function
- it contains the keyword `template`
- it makes use of a template parameter to represent a calling type

# about function parameter which is both a const and a reference

**True**

- you can not change the parameter inside the function

**False**

- a copy is made of that parameter when the function is invoked
- it only works with pointer types

# C++ functions

**True**

- uses the types of the parameters and return value to differentiate functions with the same name

**False**

- you can not have more than one function with the same name
- a function must have at least one parameter
- the first parameter of a function does not require any type information

# STL iterators

**True**

- you can treat them as if they were pointers

**False**

- you can not use them in conjunction with an STL container
- iterators are not templated elements

# `m` of type `map<string, long>`

**True**

- `m["abc"] = 2` assigns the value 2 to the key `"abc"`

**False**

- `m` has no order to its elements
- `cout << m` is a legal operation

# algorithms to multiply in `vector<long>`

**True**

- accumulate

**False**

- copy
- transform
- sort
