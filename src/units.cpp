#include "units.h"

#include <cstdio>
#include <string>
#include <regex>
#include <iostream>
#include <strstream>
#include <vector>

using std::string;
using std::strstream;
using std::vector;
using std::regex;
using std::istream;
using std::ostream;

namespace units {

// ----------------------------------------------------------------------------
// ---[ function for check ]---------------------------------------------------
// ----------------------------------------------------------------------------

bool is_digit(char ch) {
    if(ch >= '0' && ch <= '9') {
        return true;
    } else {
        return false;
    }
}

bool is_digit(string str) {
    // if there is at least one char is not digit then the string is not digit
    for(auto ch_ptr = str.begin(); ch_ptr != str.end(); ++ch_ptr) {
        if(!is_digit(*ch_ptr)) {
            return false;
        }
    }
    // if all char is digit then the string is digit
    return true;
}

bool is_email(string str) {
    // if the format is like "abc@abc.abc"
    regex EmailPattern(R"(^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$)");
    std::match_results<string::const_iterator> Result;
    if(std::regex_match(str, Result, EmailPattern)) {
        return true;
    } else {
        return false;
    }
}

bool is_not_empty(string str) {
    return str.size() != 0;
}

// ----------------------------------------------------------------------------
// ---[ function for repr-output ]---------------------------------------------
// ----------------------------------------------------------------------------

string repr(string str) {
    string result;
    result += "\'";

    for (auto it = str.begin(); it != str.end(); ++it) {
        int temp_int;
        switch(*it) {
        case '\\':
            result += "\\\\";
            break;
        case '\'':
            result += "\\\'";
            break;
        case '\"':
            result += "\\\"";
            break;
        case '\n':
            result += "\\n";
            break;
        case '\r':
            result += "\\r";
        case '\t':
            temp_int = (4 - result.size())?(4 - result.size()):4;
            result += string(temp_int, ' ');
            break;
        }
    }

    result += "\'";
    return result;
}

// ----------------------------------------------------------------------------
// ---[ function for input ]---------------------------------------------------
// ----------------------------------------------------------------------------
vector<string> split(string str) {
    regex space_re(R"(\s+)");
    return vector<string>(
        std::sregex_token_iterator(str.begin(), str.end(), space_re, -1),
        std::sregex_token_iterator()
    );
}

// ----------------------------------------------------------------------------
// ---[ function for input ]---------------------------------------------------
// ----------------------------------------------------------------------------
istream& input(string info) {
    std::cout << ' ' << info << " > ";
    return std::cin;
}

istream& input(ostream& out, istream& in, string info) {
    out << ' ' << info << " > ";
    return in;
}

}
