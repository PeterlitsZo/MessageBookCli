#ifndef PETERLITS_CLASSES_H__
#define PETERLITS_CLASSES_H__

#include <ostream>
#include <vector>
#include <string>
#include <iostream>

class Cls {
public:
    Cls();
    Cls(std::vector<std::string> vec_str);

    friend std::ostream& operator<<(std::ostream& out, const Cls& self);
    friend std::istream& operator>>(std::ostream& out, Cls& self);

    std::vector<std::string>::iterator begin();
    std::vector<std::string>::const_iterator cbegin() const;
    std::vector<std::string>::iterator end();
    std::vector<std::string>::const_iterator cend() const;
private:
    std::vector<std::string> Classes_;
};

#endif // for ifndef PETERLITS_CLASSES_H__
