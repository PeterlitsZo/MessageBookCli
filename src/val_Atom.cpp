#include "val.h"

#include <functional>
#include <string>
#include <iostream>
#include "units.h"

#include "../include/logging/easylogging++.h"

using std::string;

namespace mbc {

namespace Val {


// clear self
_ValAtom::~_ValAtom() {
    if (*count_ == 1) {
        delete vaild_checker_;
    }
}


_ValAtom::_ValAtom() : ValBase() {
    vaild_checker_ = new std::function<bool(const string& str)>(
                            [](const string& str){return true;}
                     );
    *type_ = Type(ATOM);
}


_ValAtom::_ValAtom(const _ValAtom& other) : ValBase(other) {
    vaild_checker_ = other.vaild_checker_;
}


// Atom can set self by string (wow, it can deal with string)
_ValAtom& _ValAtom::set(const string& str) {
    if ((*vaild_checker_)(str)) {
        *is_vaild_ = true;
        init_(str);
    } else {
        *is_vaild_ = false;
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
