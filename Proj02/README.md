# Juggler sequence

## Assignment Overview

This assignment will give you experience on the use of loop and conditional statements. We are going work with the [juggler sequence](https://en.wikipedia.org/wiki/Juggler_sequence).

## Background

The juggler sequence is another of the well known sequences similar to the Collatz sequence. It has the following definition:

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj02/proj02.png)

The └ ┘ symbol is the **floor** function, rounding any floating point value **down** to an integer. It is not rounding as you would typically define it. It is essentially truncation of the fractional part, leaving the integer part of the floating point number. It returns a floating point number.

- floor(123.23) is 123.0
- floor(123.999) is 123.0

Some things to note about the juggler sequence:

- Every known starting number eventually ends in the value 1. At that point the sequence ends.
- The numbers can get quite large, so make sure you use the correct type. Even with the correct types you can exceed the size of a long integer.
- The cmath library provides a number of useful methods including pow, sqrt and floor (look them up). Some example sequences are on the Wikipedia page.

# Project Description / Specification

## Input

**Two integers**

- a low value and a high value (in that order) indicating a range. You are to generate the Juggler sequence for every number in that range and report as follows.
- if the high value is strictly less than the low value, output Error and quit.

## Output

If high is greater than or equal to low, on two separate lines you will print:

- the sequence of the longest length. You will print the starting number, a space, and the length.
- the sequence that generated the largest number. You will print the starting number, a space, and the largest number generated.
