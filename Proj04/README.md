# Number Classifier

## Assignment Overview

This assignment will give you more experience on the use of functions and your first experience with the use of strings.

## Background

You are going to make a **number classifier**. A number classifier takes in a string and decides what kind of number the string represents. We will deal with the format of numbers that C++11 requires.

In mathematics most numbers are expressed in a base-10 numeral system. However, we can also express the same number using a different system. For example, 5 in decimal system can be expressed as 101 in a base-2 system (Binary system). Your number classifier should distinguish the type of input number in string form.

## The Problem

Here as some facts about number strings and how they are represented in C++11.

### Binary numbers

This is a base-2 system as we discussed above. There are only two numeric symbols in this system: 0 and 1. To express a binary number in computer science, we will add a prefix so it is not confused with other systems. For binary system, we use 0b as prefix. For example, the binary number 101 can be expressed in C++11 as 0b101. Binary numbers may be negative and preceded by a minus sign. [For more details](https://en.wikipedia.org/wiki/Binary_number)

### Octal numbers

The Octal numeral system is a base-8 system. An octal number can only use the symbols (0-7). In C++11 we designate a number as octal when we prefix the number with 0. Octal numbers may be negative and preceded by a minus sign. [For more details](https://en.wikipedia.org/wiki/Octal)

### Hexadecimal numbers

Hexadecimal numeral system is a base-16 system. It uses the symbols(0-9 and a-f). In C++11 we use 0x as a prefix. Hex numbers can be negative and may be preceded by a minus sign. [For more details](https://en.wikipedia.org/wiki/Hexadecimal)

### Decimal numbers

For all other numbers without a prefix, we can assume it is base ten number. If the input is a base ten number, you are required to further classify it into one two sub categories: integer or floating point.

- Integer numbers have no decimal point (and thus no numbers behind the decimal point). Integer numbers can be negative and preceded by a minus sign.
- Floating points can be expressed in fixed notation (numbers including a decimal point) or in scientific notation. [For more details](https://en.wikipedia.org/wiki/Scientific_notation)
   - fixed: decimal number, decimal point, decimal point, for example: 123.456. Number can be negative and preceded by a minus sign.
