#include "classes.h"

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>

#include "units.h"

using std::ostream;
using std::istream;
using std::string;
using std::getline;
using std::vector;

Cls::Cls() {
}

Cls::Cls(vector<string> vec_str) {
    Classes_ = vec_str;
}

ostream& operator<<(ostream& out, const Cls& self) {
    out << units::repr(self.cbegin(), self.cend());
    return out;
}

istream& operator>>(istream& in, Cls& self) {
    string str;
    getline(in, str);
    auto elements = units::split(str);
    // for(auto it = elements.begin(), it != elements.end(); ++it) {
    //     self.Classes_.push_back(*it);
    // }
    return in;
}

vector<string>::iterator Cls::begin() {
    return Classes_.begin();
}

vector<string>::const_iterator Cls::cbegin() const {
    return Classes_.cbegin();
}

vector<string>::iterator Cls::end() {
    return Classes_.end();
}

vector<string>::const_iterator Cls::cend() const {
    return Classes_.cend();
}
