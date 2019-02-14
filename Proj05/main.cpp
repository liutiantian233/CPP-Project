// whatever includes you need
#include <iostream>  // the head File
using std::cout; using std::cin; using std::endl; using std::boolalpha;  // C++ STL

#include <string>  // the head File
using std::string; using std::to_string;  // C++ STL

#include <cmath>

string lower_case(string s) {
    string str;
    for (char c : s)
        str += tolower(c);
    return str;
}

string to_binary(char c) {
    string empty;
    if (islower(c)) {
        int num = c - 'a';
        string str;
        while (num) {
            string s = to_string(num % 2);
            num = num / 2;
            str = s + str;
        }
        str = "00000" + str;
        string remainder(str, str.size()-5);
        return remainder;
    }
    else
        return empty;
}

char from_binary(string bit_str) {
    if (bit_str.size() == 5) {
        double exp = 4, num = 0;
        char bit;
        for (char c : bit_str) {
            if (c == '0' or c == '1')
                num = num + (int(c)-48) * pow(2.0, exp);
            --exp;
        }
        bit = 'a' + num;
        if (islower(bit))
            return bit;
    }
    return NULL;
}

bool check_message(string plaintext, string secret_message) {
    int num_plaintext = 0, num_secret_message = 0;
    for (char c : plaintext) {
        if (isalnum(c)) {
            ++num_plaintext;
        }
    }
    for (char c : secret_message) {
        if (isalnum(c)) {
            ++num_secret_message;
        }
    }
    if (num_plaintext > 5 * num_secret_message)
        return true;
    return false;
}

string encode(string plaintext, string secret_message) {
    plaintext = lower_case(plaintext);
    secret_message = lower_case(secret_message);
    string bin;
    if (check_message(plaintext, secret_message)) {
        for (char c : secret_message) {
            bin += to_binary(c);
        }
        int index = 0;
        for (char c : bin) {
            while (!isalpha(plaintext[index]))
                ++index;
            if (c == '1')
                plaintext[index] = toupper(plaintext[index]);
            ++index;
        }
        return plaintext;
    }
    return "Error";
}

string decode(string to_decode) {
    string new_decode, bin;
    for (char c : to_decode) {
        if (isalpha(c))
            new_decode += c;
    }
    for (char c : new_decode) {
        if (islower(c))
            bin += '0';
        else
            bin += '1';
    }
    string code;
    int index = 0;
    for (auto i = 0; i < bin.size() / 5; ++i) {
        char c;
        c = from_binary(bin.substr(index, 5));
        code += c;
        index += 5;
    }
    return code;
}

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

    }  // of switch
}  // of main