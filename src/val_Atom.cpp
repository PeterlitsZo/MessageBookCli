#include "val.h"

#include <string>
#include <iostream>
#include "units.h"

#include "../include/logging/easylogging++.h"

using std::string;

namespace mbc {

namespace Val {


// clear self
_ValAtom::~_ValAtom() {
    ; // do nothing
}


// Atom can set self by string (wow, it can deal with string)
_ValAtom& _ValAtom::set(const string& str) {
    std::cout << "the set value is " << str << "." << std::endl;
    if (vaild_checker_(str)) {
        std::cout << "it is vaild" << std::endl;
        is_vaild_ = true;
        init_(str);
    } else {
        std::cout << "it is not vaild" << std::endl;
        is_vaild_ = false;
        init_();
    }
    return *this;
}


// the operator will do the same work like set function
_ValAtom& _ValAtom::operator=(const string& str) {
    return set(str);
}


} // for namespace Val

} // for namespace mbc
