#include "val.h"

#include <string>
#include <iostream>

#include "../../include/rapidjson/document.h"

using std::string;

using rapidjson::Document;

namespace mbc {

namespace Val {

// definition the static varible doc_
Document ValBase::doc_;


// clear self
ValBase::~ValBase() {
    -- *count_;
    if(*count_ == 0) {
        delete count_;
        delete invaild_waring_;
        delete is_vaild_;
        delete type_;
    }
}


ValBase::ValBase() {
    count_          = new int(1);
    invaild_waring_ = new string("[invaild val-base]");
    is_vaild_       = new bool(false);
    type_           = new Type;

    *type_          = BASE;
}

ValBase::ValBase(const ValBase& other) {
    count_          = other.count_;
    invaild_waring_ = other.invaild_waring_;
    is_vaild_       = other.is_vaild_;
    type_           = other.type_;

    // add the ref-counter with 1
    ++ *count_;
}


// return self's type
const Type& ValBase::type () const {
    return *type_;
}


// return self by the form of string
const string ValBase::str() const {
    if (*is_vaild_) {
        return str_();
    } else {
        return *invaild_waring_;
    }
}


// check if self is vaild.
bool ValBase::vaild() const {
    return *is_vaild_;
}


ValBase::operator bool() const {
    return *is_vaild_;
}


} // for namespace Val

} // for namespace mbc

