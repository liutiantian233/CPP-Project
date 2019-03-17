# `friend` designation

it is a push, not a pull (True)

it indicates permission to access private class elements 表示访问私有类元素的权限 (True)

it can apply to both a class and a function (True)

# difference capacity and size in vector

**size** is how many elements are in the vector

**capacity** is how many it could hold before growing

# `cin.ignore` method

removes characters from the input stream (True)

ignores the last cin operation (False)

clears any errors, resets cin to be good (False)

closes the cin stream (False)

## `cin.ignore(100)`

ignore all input from cin except for the value 100 (False)

prevent cin from getting the value 100 from the input stream (False)

empty the cin buffer of 100 inputs stored there (True)

stop input for the next 100 milliseconds (False)

# C++ map STL container

it is a sequence (False)

it consists **only** of a series of keys (False)

requires a single template type to make a variable of type map (False)

## not method of map

find (False)

size (False)

push_front (True)

count (False)

# operator *

as a binary operation it represents multiply (True)

in a declaration it represents a pointer type (True)

in a declaration it represents a reference type (False)

as a unary operation it represents de-reference (True)

as a unary operation it represents size_of (False)

in the expression 1 * 2 it represents multiplication (True)

in the declaration long * p it represents dereferencing of a pointer (False)

in cout << * p, the * represents the creation of a pointer variable p (False)

# special variable `this`

you can **directly** assign it a new value in a class method (False)

it is automatically set by C++ to the address of the calling variable (True)

it is an integer type (False)

the programmer can **directly** assign it a new value in a class method (False)

the programmer must set it to use it in a class method (False)

it is a pointer type (True)

# C++ random numbers

they generate the same sequence when starting from the same seed (True)

when used in conjunction with a distribution, the distribution uses the random number generator as an argument (True)

C++ has multiple versions of random number generators (True)

# constructor

## about C++ constructors

they have the same name as the struct in which they are contained (True)

they return the newly made element of the struct type (False)

they can not take any arguments (False)

they can not be defined inside of a struct (False)

they require a return statement to return newly made struct type (False)

they can be overloaded for different parameter lists (True)

## designation on a constructor ( = default)

over-rides **all** user-provided constructors to use only the synthesized constructor (False)

sets the permissions of private data members to public (False)

for the default constructor, use the synthesized constructor (True)

# `lambda` function

it is a nameless function (True)

they are often used in conjunction with STL algorithms (True)

they have a capture list (True)

it is a function and can be invoked like a function (True)

it has a name (False)

it can not be used in a generic algorithm (False)

is commonly used as part of a generic algorithm (True)

# templated function

it is itself not a function, but a way to create a function (True)

it contains the keyword template (True)

it makes use of a template parameter to represent a calling type (True)

# about function parameter which is both a const and a reference

a copy is made of that parameter when the function is invoked (False)

you can not change the parameter inside the function (True)

it only works with pointer types (False)

# C++ functions

you can not have more than one function with the same name (False)

a function must have at least one parameter (False)

uses the types of the parameters and return value to differentiate functions with the same name (True)

the first parameter of a function does not require any type information (False)

# STL iterators

you can treat them as if they were pointers (True)

you can not use them in conjunction with an STL container (False)

iterators are not templated elements (False)

# methods

a method can be part of a `struct` (True)

it is called in the context of an object using a dot call (True)

in calling a method the `this` pointer is assigned by the compiler (True)

## `explicit` designation

used to prevent implicit conversion (True)

indicates permission to access private class elements (False)

method spelling must be explicit (False)

# m of type `map<string,long>`

m has no order to its elements (False)

m[abc] = 2 assigns the value 2 to the key abc (True)

cout << m is a legal operation (False)

## type returned by insert

long (False)

long& (False)

string (False)

bool (False)

# algorithms to multiply

copy (False)

transform (False)

sort (False)

accumulate (True)

# proper interpretation var1 -> y

return the data member y of var1 (False)

dereference the pointer var1 and return its data member y (True)

dereference the pointer y and return its value (False)

set var1 to y (False)

# string::npos

it is the maximum number of positions in a string (False)

in a substring operation, it signifies from the beginning of the string (False)

it is returned when a find operation fails on a string (True)

# constitutes to conversion for class named MyClass

MyClass(string) (True)

MyClass(long, long) (False)

MyClass(MyClass&) (False)

# commands allocates dynamic memory during program runtime

copy (False)

add (False)

create (False)

new (True)

# C++ exceptions

potential elements that might throw are wrapped in a try block (True)

if an error is thrown, control moves to the catch block of the same error type (True)

an uncaught exception will halt the program (True)
