#ifndef PETERLITS_UNITS_H__
#define PETERLITS_UNITS_H__

#include <istream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

namespace units {

// function for check
bool is_digit(char ch);
bool is_digit(std::string str);
bool is_email(std::string str);
bool is_not_empty(std::string str);

// function for repr-output
std::string repr(std::string str);

std::string repr(char* str);
std::string repr(const char* str);

template <typename T>
std::string repr(const T& value) {
    std::stringstream ss;
    ss << value;
    std::string result;
    ss >> result;

    return result;
}

template <typename T>
std::string repr(const T& begin, const T& end) {
    // if the size == 0:
    if(end - begin == 0) {
        return "[]";
    }

    // else the size != 0:
    std::string result;
    result += "[";

    // loop to repr the content
    T it;
    for(it = begin; it != end - 1; ++it) {
        result += repr(*it);
        result += ", ";
    }
    result += repr(*it);

    result += "]";
    return result;
}

// split string
std::vector<std::string> split(std::string str);

// function for input
class Input {
public:
    Input(std::istream& in, std::ostream& out);
    std::istream& operator() (std::string info);
private:
    std::istream& in_;
    std::ostream& out_;
};
std::istream& input(std::string info);
std::istream& input(std::ostream& out, std::string info);

bool start_with(std::string full, std::string sub);

} // for namespace units

// ----------------------------------------------------------------------------

#endif // for PETERLITS_UNITS_H__

