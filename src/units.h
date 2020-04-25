#ifndef PETERLITS_UNITS_H__
#define PETERLITS_UNITS_H__

#include <string>
#include <regex>
using std::string;

namespace units {

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
    std::regex EmailPattern(R"(^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$)");
    std::match_results<string::const_iterator> Result;
    if(std::regex_match(str, Result, EmailPattern)) {
        return true;
    } else {
        return false;
    }
}

}

#endif

