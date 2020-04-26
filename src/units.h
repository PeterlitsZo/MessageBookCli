#ifndef PETERLITS_UNITS_H__
#define PETERLITS_UNITS_H__

#include <istream>
#include <string>
#include <iostream>

namespace units {

bool is_digit(char ch);
bool is_digit(std::string str);
bool is_email(std::string str);
bool is_not_empty(std::string str);

std::istream& input(std::string info);

}

#endif // for PETERLITS_UNITS_H__

