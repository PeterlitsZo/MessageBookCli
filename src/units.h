#ifndef PETERLITS_UNITS_H__
#define PETERLITS_UNITS_H__

#include <istream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <exception>

namespace units {

// ----------------------------------------------------------------------------
// ---[ exception ]------------------------------------------------------------
// ----------------------------------------------------------------------------

struct bad_parser : public std::exception {
    std::string msg_;

    bad_parser(const char* msg) : msg_(msg) {}
    bad_parser(std::string msg) : msg_(msg) {}
    const char* what() throw() {
        return msg_.c_str();
    }
};

// ----------------------------------------------------------------------------
// ---[ hash ]-----------------------------------------------------------------
// ----------------------------------------------------------------------------

std::string md5(std::string str);

// ----------------------------------------------------------------------------
// ---[ check ]----------------------------------------------------------------
// ----------------------------------------------------------------------------

// ---[ function for check ]---------------------------------------------------
bool is_digit(char ch);
bool is_digit(std::string str);
bool is_email(std::string str);
bool is_not_empty(std::string str);


// ----------------------------------------------------------------------------
// ---[ string ]---------------------------------------------------------------
// ----------------------------------------------------------------------------

// ---[ function for repr-output ]---------------------------------------------
std::string repr(std::string str);

std::string repr(char* str);
std::string repr(const char* str);

template <typename T>
std::string repr(const T& value) {
    std::stringstream ss;
    ss << value;

    std::string result;
    std::getline(ss >> std::ws, result);

    return result;
}

template <typename T>
std::string repr(const T& begin, const T& end) {
    std::string result;
    result += "[";

    // loop to repr the content
    T it = begin;
    if(begin != end) {
        result += repr(*begin);
        it ++;
    }
    for(; it != end; ++it) {
        result += ", ";
        result += repr(*it);
    }

    result += "]";
    return result;
}


// ---[ split string ]---------------------------------------------------------
std::vector<std::string> split(std::string str);


// ---[ warp string ]----------------------------------------------------------
std::string hard_warp(std::string str, int hard);


// ---[ add head ]-------------------------------------------------------------
std::string add_head(std::string str, std::string head);


// ---[ parse string ]---------------------------------------------------------

std::string parse_str_repr(std::string str);
std::vector<std::string> parse_vecstr_repr(std::string str);

// ----------------------------------------------------------------------------
// ---[ input ]----------------------------------------------------------------
// ----------------------------------------------------------------------------

// ---[ function for input ]---------------------------------------------------
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

#endif // for PETERLITS_UNITS_H__

