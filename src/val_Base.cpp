#include "val.h"

#include <string>

#include "../include/rapidjson/document.h"

using std::string;

using rapidjson::Document;

namespace mbc {

namespace Val {

// definition the static varible doc_
Document ValBase::doc_;


// clear self
ValBase::~ValBase() {
    ; // do nothing
}


// return self's type
const Type& ValBase::type () const {
    return type_;
}


// return self by the form of string
const string ValBase::str() const {
    if (is_vaild_) {
        return str_();
    } else {
        return *invaild_waring_;
    }
}


// check if self is vaild.
bool ValBase::vaild() const {
    return is_vaild_;
}

} // for namespace Val

} // for namespace mbc
