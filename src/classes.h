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
    friend std::istream& operator>>(std::istream& in, Cls& self);

    template<typename T>
    void extend(T begin, T end);

    std::vector<std::string>::iterator begin();
    std::vector<std::string>::const_iterator cbegin() const;
    std::vector<std::string>::iterator end();
    std::vector<std::string>::const_iterator cend() const;
private:
    std::vector<std::string> Classes_;
};

std::ostream& operator<<(std::ostream& out, const Cls& self);
std::istream& operator>>(std::istream& in, Cls& self);

// ---[ impl function ]--------------------------------------------------------
template<typename T>
void Cls::extend(T begin, T end) {
    Classes_.insert(Classes_.end(), begin, end);
}

#endif // for ifndef PETERLITS_CLASSES_H__
