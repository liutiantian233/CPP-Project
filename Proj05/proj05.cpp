////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #05   Secret
//
//  Define the head File "iostream" and "cmath" and "string"
//    use the C++ Standard Library headers
//    the cmath is math tools
//    the string is string tools
//
//  Defining function:
//    lower_case, to_binary, from_binary, check_message, encode, decode
//
//    lower_case: returns the lower case version of the input string s.
//    to_binary: returns 5 bit string that is the index of the character argument.
//    from_binary: returns the character that the 5 bit binary string bit_str represents.
//    check_message: returns true if there are at least 5x the count of characters in secret_message as in plaintext.
//    encode: plaintext and secret_message should be converted to lower case by lower_case.
//    decode: returns the original secret_message as a string.
//
//  Defining main function:
//    use the all function and switch case statement.
//
////////////////////////////////////////////////////////////////////////////////

// whatever includes you need
#include <iostream>  // the head File
using std::cout; using std::cin; using std::endl; using std::boolalpha;  // C++ STL

#include <string>  // the head File
using std::string; using std::to_string;  // C++ STL

#include <cmath>  // the head File

// returns the lower case version of the input string s.
string lower_case(string s) {

    string str;

    // for loop in the string
    for (char c : s)
        str += std::to_string(tolower(c));  // use the tolower

    return str;
}

// returns 5 bit string that is the index of the character argument.
string to_binary(char c) {

    string empty;

    // if the char c is lower
    if (islower(c)) {

        int num = c - 'a';
        string str;

        // while loop for divide by 2
        while (num) {
            string s = to_string(num % 2);
            num = num / 2;
            str.insert(0, s);
        }

        // make the string is 5 num
        str = "00000" + str;
        string remainder(str, str.size() - 5);

        return remainder;
    }

    else
        return empty;
}

// returns the character that the 5 bit binary string bit_str represents.
char from_binary(string bit_str) {

    // Determine if it is 5 digits
    if (bit_str.size() == 5) {

        double exp = 4, num = 0;
        char bit;

        // for loop in bit_str
        for (char c : bit_str) {

            if (c == '0' or c == '1')
                num = num + (int(c) - 48) * pow(2.0, exp);

            --exp;
        }

        bit = static_cast<char>('a' + num);  // make the bit is char

        if (islower(bit))
            return bit;
    }

    return '\0';  // return NULL
}

// returns true if there are at least 5x the count of characters in secret_message as in plaintext.
bool check_message(string plaintext, string secret_message) {

    int num_plaintext = 0, num_secret_message = 0;

    // for loop in plaintext
    for (char c : plaintext) {
        if (isalnum(c)) {
            ++num_plaintext;
        }
    }

    // for loop in secret_message
    for (char c : secret_message) {
        if (isalnum(c)) {
            ++num_secret_message;
        }
    }

    return num_plaintext > 5 * num_secret_message;
}

// plaintext and secret_message should be converted to lower case by lower_case.
string encode(string plaintext, string secret_message) {

    plaintext = lower_case(plaintext);
    secret_message = lower_case(secret_message);

    string bin;

    // use the check_message
    if (check_message(plaintext, secret_message)) {

        for (char c : secret_message) {
            bin += to_binary(c);
        }

        auto index = 0;

        for (char c : bin) {

            while (!isalpha(plaintext[index]))
                ++index;

            if (c == '1')
                plaintext[index] = static_cast<char>(toupper(plaintext[index]));

            ++index;
        }

        return plaintext;
    }

    return "Error";
}

// returns the original secret_message as a string.
string decode(string to_decode) {

    string new_decode, bin;

    // for loop in to_decode
    for (char c : to_decode) {
        if (isalpha(c))
            new_decode += c;
    }

    // for loop in new_decode
    for (char c : new_decode) {
        if (islower(c))
            bin += '0';
        else
            bin += '1';
    }

    string code;
    unsigned long index = 0;

    for (auto i = 0; i < bin.size() / 5; ++i) {
        char c;
        c = from_binary(bin.substr(index, 5));
        code += c;
        index += 5;
    }

    return code;
}

// main is below. You cannot modify main
int main() {

    cout << boolalpha;
    
    int test_num;
    cin >> test_num;

    switch (test_num) {

        case 1 : {
            string s;
            getline(cin, s);
            cout << lower_case(s) << endl;
            break;
        }  // of case 1

        case 2 : {
            char c;
            cin >> c;
            cout << to_binary(c) << endl;
            break;
        }  // of case 2

        case 3 : {
            string n;
            cin >> n;
            cout << from_binary(n) << endl;
            break;
        }  // of case 3

        case 4 : {
            string plain, secret;
            getline(cin, plain);
            getline(cin, secret);
            cout << check_message(plain, secret) << endl;
            break;
        }  // of case 4

        case 5 : {
            string plain, secret;
            getline(cin, plain);
            getline(cin, secret);
            cout << encode(plain, secret) << endl;
            break;
        }  // of case 5

        case 6 : {
            string encoded;
            getline(cin, encoded);
            cout << decode(encoded) << endl;
            break;
        }  // of case 6

        default:break;

    }  // of switch
}  // of main
