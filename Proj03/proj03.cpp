////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #03   Achilles Number
//
//  Define the head File "iostream" and "cmath"
//    use the C++ Standard Library headers
//    the cmath is math tools
//
//  Defining function:
//    the is_prime, is_powerful, is_perfect_power, is_achilles
//
//    is_prime: use one for loop and one if statement.
//    is_powerful: use four if statement and one for loop.
//    is_perfect_power: use two if statement, one for loop and one while loop.
//    is_achilles: use the is_powerful and is_perfect_power function.
//
//  Defining main function:
//    use the all function and switch case statement.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>  // the head File
using std::cout; using std::cin; using std::endl; using std::boolalpha;  // C++ STL

// add any other includes you like.
#include <cmath>

// functions go here
bool is_prime(long num) {
    long long i;

    for (i = 2; i * i <= num; ++i) {
        if (num % i == 0)  // if there are number can divides
            return false;
    }
    return true;
}

bool is_powerful(long num) {

    // 1 is a powerful number
    if (num == 1)
        return true;

    else {
        for (long i = 2; i < num; ++i) {

            if (num % i == 0) {
                if (is_prime(i)) {

                    if (num % (i * i) == 0)  // if i^2 is number.
                        return true;  // it is a powerful number
                }
                else
                    return false;
            }
            else
                return false;
        }
    }
    return false;
}

bool is_perfect_power(long num) {

    // 1 is a perfect power
    if (num == 1)
        return true;

    else {  // this is while loop in for loop
        for (long i = 2; i < num; ++i) {
            double root = 2;  // set a double number

            while (pow (i, root) <= num) {

                if (pow (i, root) == num)
                    return true;
                ++root;  // add one in root
            }
        }
    }
    return false;
}

bool is_achilles(long num) {
    // use the is_powerful and is_perfect_power function.
    return is_powerful(num) && !is_perfect_power(num);
}

// main is below. You cannot modify main
int main() {
    cout << boolalpha;

    int test_case;
    cin >> test_case;

    switch (test_case) {

        case 1 : {
            long num;
            cin >> num;
            cout << is_prime(num) << endl;
            break;
        }  // of case 1

        case 2 : {
            long num;
            cin >> num;
            cout << is_powerful(num) << endl;
            break;
        }  // of case 2

        case 3 : {
            long num;
            cin >> num;
            cout << is_perfect_power(num) << endl;
            break;
        }  // of case 3

        case 4 : {
            long num;
            cin >> num;
            cout << is_achilles(num) << endl;
            break;
        }  // of case 4

    }  // of switch
}  // of main
