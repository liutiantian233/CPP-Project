////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #04   Classify Numbers
//
//  Define the head File "iostream" and "cmath" and "cctype"
//    use the C++ Standard Library headers
//    the cmath is math tools
//    the cctype is char tools
//
//  Defining function:
//    valid_hex, valid_octal, valid_binary, valid_int, valid_float, classify_string
//
//    valid_hex: Return true if the given string is a valid hexadecimal number.
//    valid_octal: Return true if the given string is a valid octal number.
//    valid_binary: Return true if the given string is a valid binary number.
//    valid_int: Return true if the given string is a valid integer.
//    valid_float: Return true if the given string is a valid floating point number.
//    classify_string: Use the all function.
//
//  Defining main function:
//    use the all function and switch case statement.
//
////////////////////////////////////////////////////////////////////////////////

// whatever includes you need
#include <iostream>  // the head File
using std::cout; using std::cin; using std::endl; using std::boolalpha;  // C++ STL

#include <string>
using std::string;

#include <cctype>
using std::isdigit; using std::isalpha;

bool valid_hex(string str) {
    if (str[0] == '-')
        str = str.substr(1);
    if (str.substr(0, 2) == "0x") {
        str = str.substr(2);
        for (int i = 0; i < str.size(); ++i) {
            if (!isalnum(str[i]))
                return false;
            if (isalpha(str[i]) and str[i] > 'f')
                return false;
        }
        return true;
    }
    return false;
}

bool valid_octal(string str) {
    if (str[0] == '-')
        str = str.substr(1);
    if (str.substr(0, 1) == "0") {
        str = str.substr(1);
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] > '7' or !isdigit(str[i]))
                return false;
        }
        return true;
    }
    return false;
}

bool valid_binary(string str) {
    if (str[0] == '-')
        str = str.substr(1);
    if (str.substr(0, 2) == "0b") {
        str = str.substr(2);
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] > '1' or !isdigit(str[i]))
                return false;
        }
        return true;
    }
    return false;
}

bool valid_int(string str) {
    if (str[0] == '-')
        str = str.substr(1);
    for (int i = 0; i < str.size(); ++i) {
        if (not isdigit(str[i]))
            return false;
    }
    return true;
}

bool valid_float(string str) {
    string exp;
    if (str[0] == '-')
        str = str.substr(1);
    if (valid_int(str))
        return false;
    for (unsigned long i = 0; i < str.size(); ++i) {
        if (str[i] == 'e' or str[i] == '.') {
            exp = str.substr(++i);
            if (exp.find('e') != string::npos or exp.find('.') != string::npos)
                return false;
            if (!valid_int(exp))
                return false;
            continue;
        }
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

string classify_string(string str) {
    string error = "false";
    string hex = "hex", octal = "octal", binary = "binary", integer = "int", floating = "float";
    if (valid_hex(str))
        return hex;
    if (valid_octal(str))
        return octal;
    if (valid_binary(str))
        return binary;
    if (valid_int(str))
        return integer;
    if (valid_float(str))
        return floating;
    return error;
}

// main is below. You cannot modify main
int main() {

    cout << boolalpha;
    int test_num;
    cin >> test_num;

    switch (test_num) {

        case 1 : {
            string to_test;
            cin >> to_test;
            cout << valid_hex(to_test) << endl;
            break;
        }  // of case 1

        case 2 : {
            string to_test;
            cin >> to_test;
            cout << valid_octal(to_test) << endl;
            break;
        }  // of case 2

        case 3 : {
            string to_test;
            cin >> to_test;
            cout << valid_binary(to_test) << endl;
            break;
        }  // of case 3

        case 4 : {
            string to_test;
            cin >> to_test;
            cout << valid_float(to_test) << endl;
            break;
        }  // of case 4

        case 5 : {
            string to_test;
            cin >> to_test;
            cout << valid_int(to_test) << endl;
            break;
        }  // of case 5

        case 6 : {
            string to_test;
            cin >> to_test;
            cout << classify_string(to_test) << endl;
            break;
        }  // of case 6

    }  // of switch
}  // of main
