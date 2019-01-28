# Achilles Number

## Assignment Overview

This assignment will give you more experience on the use of loops and conditionals, and introduce the use of functions.

## Background

There are all sorts of special numbers, much like perfect numbers that we saw in Python. Take a look sometime at [this link](http://mathworld.wolfram.com/topics/SpecialNumbers.html) for a big list. One such class of numbers is called **Achilles Numbers**. Great name! An Achilles has two special features based on its **prime factors** using some unusual named properties of numbers:

- the number should be **powerful**.
- the number should not be a **perfect power**.

Lets look at all three of those properties.

## Prime Factors

The prime factors of any integer should be familiar. You find all the prime integers that divide exactly (without remainder) into an integer. We exclude 1 (which is a factor of every integer) and the number itself (which, again, is a prime factor of every particular number).

- for example, the prime factors of 30 are 2, 3, 5 since 2 * 3 * 5 = 30. Note that 6, 15 and 10 are also factors but they are **not prime factors**.
- take a look at [this link](https://en.wikipedia.org/wiki/Table_of_prime_factors) for a table of the prime factors of many numbers.

## Powerful Number

A powerful number is an integer with the following property. For every prime factor in the number, the square of the prime factor must divide exactly (without remainder) into the original number.

- 30 **is not** a powerful number. Its prime factors are 2, 3, 5. 2^2 does not divide exactly into 30, 3^2 does, 5^2 does not. All of the factors squared must divide exactly into the number for it to be powerful.
- 72 **is** a powerful number. Its prime factors are 2, 3 (2^3 * 3^2 = 72). 2^2 divides exactly into 72 (18 * 4) as does 3^2 (9 * 8).

[This link](https://en.wikipedia.org/wiki/Powerful_number) gives a list of powerful numbers.

## Perfect Power

A perfect power number is an integer that can be expressed as a single expression of the form m^k. That is, there is some **integer m** which, raised to the **integer power k**, is the **integer n** in question.

## Functions

**function**: is_prime: return is **bool**. Argument is a single **long n**. If n is prime it returns **true**, otherwise it returns **false**.

**function**: is_powerful: return is **bool**. Argument is a single **long n**. If n is powerful it returns **true**, otherwise it returns **false**. Utilizes **is_prime** (or should).

**function**: is_perfect_power: return is **bool**. Argument is a single **long n**. If n is a perfect power it returns **true**, otherwise it returns **false**.

**function**: is_achilles: return is **bool**. Argument is a single **long n**. If n is an Achilles number it returns **true**, otherwise it returns **false**. Utilizes **is_powerful** and is **is_perfect_power** (or should).

## Specific Hints

If we were more knowledgeable about algorithms we could discuss how to be efficient about these checks, but for now we would just like them to work. Here are some pretty specific suggestions, but feel free to work it out for yourself.

### is_prime:

- You can check every number from 2 up to the n-1 and see if any of those numbers divides without remainder. If so, then it isn't prime. Otherwise it is.
  - you can be more efficient. What value do you really need to check up to (less than n-1)?
  - **break** can save you some computational time here.

### is_powerful:

- First, no prime number is ever powerful.
- Check every number from 2 to n-1.
  - if it divides without remainder into n, then it is a factor.
    - for all of those factors that are prime, then
      - if the square of that factor also divides without remainder into n, it is a powerful number.
    - otherwise not powerful.

