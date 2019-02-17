#include <iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include <string>
using std::string;
#include <cmath>

string lower_case(string s) {
    string new_string;
    for (auto i = 0; i < s.size(); ++i) {
        new_string = new_string + static_cast<char>(tolower(s[i]));
    }
    return new_string;
}

string to_binary(char c) {
    string s, str;
    if (islower(c)) {
        int index = c - 'a';
        for(int i = 4; i >= 0; --i) {
            if(index & (1 << i)) {
                str = str + "1";
                continue;
            }
            str = str + "0";
        }
        return str;
    }
    return s;
}

char from_binary(string bit_str) {
    char c;
    if (bit_str.size() != 5)
        return NULL;
    else {
        int num = 0;
        for (auto i = 0; i < bit_str.size(); ++i) {
            if (bit_str[i] == '0' or bit_str[i] == '1') {
                if (bit_str[i] == '0')
                    num += 0 * pow(2, 4 - i);
                if (bit_str[i] == '1')
                    num += 1 * pow(2, 4 - i);
            }
        }
        c = 'a' + num;
    }
    if (islower(c))
        return c;
    return NULL;
}

bool check_message(string plaintext, string secret_message) {
    int p = 0, m = 0;
    for (auto i = 0; i < plaintext.size(); ++i) {
        if (isalnum(plaintext[i]))
            p = p + 1;
    }
    for (auto i = 0; i < secret_message.size(); ++i) {
        if (isalnum(secret_message[i]))
            m = m + 1;
    }
    return p > 5 * m ? true : false;
}

string encode(string plaintext, string secret_message) {
    string p = lower_case(plaintext), m = lower_case(secret_message), code = "", e = "Error";
    if (check_message(p, m)) {
        for (auto i = 0; i < m.size(); ++i)
            code = code + to_binary(m[i]);
        for (auto i = 0; i < p.size(); ++i) {
            if (isalpha(p[i])) {
                if (code[0] == '1')
                    p[i] = toupper(p[i]);
                if (code.size() == 0)
                    break;
                code = code.substr(1);
            }
        }
        return p;
    }
    return e;
}

string decode(string to_decode) {
    string s, str;
    for (auto i = 0; i < to_decode.size(); ++i) {
        if (!isalpha(to_decode[i]))
            to_decode.erase(i, 1);
    }
    for (auto i = 0; i < to_decode.size(); ++i) {
        if (islower(to_decode[i])) {
            s = s + '0';
            continue;
        }
        s = s + '1';
    }
    auto time = s.size() / 5;
    for (auto i = 0; i < time; ++i) {
        char c = from_binary(s.substr(5 * i, 5));
        str = str + c;
    }
    return str;
}
