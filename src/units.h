#ifndef PETERLITS_UNITS_H__
#define PETERLITS_UNITS_H__

#include <istream>
#include <string>
#include <iostream>
#include <vector>
#include <strstream>

namespace units {

// function for check
bool is_digit(char ch);
bool is_digit(std::string str);
bool is_email(std::string str);
bool is_not_empty(std::string str);

// function for repr-output
std::string repr(std::string str);

template <typename T>
std::string repr(T value) {
    std::strstream ss;
    ss << value;
    std::string result;
    ss >> result;

    return result;
}

template <typename T>
std::string repr(T begin, T end) {
    std::string result;
    result += "[";

    // loop to repr the content
    T it;
    for(it = begin; it != end - 1; ++it) {
        result += repr(*it);
        result += " ,";
    }
    result += repr(*it);

    result += "]";
    return result;
}

// split string
std::vector<std::string> split(std::string str);

// function for input
std::istream& input(std::string info);
std::istream& input(std::ostream& out, std::string info);

}

// ----------------------------------------------------------------------------

#endif // for PETERLITS_UNITS_H__

