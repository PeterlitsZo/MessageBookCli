#include "val.h"

#include <string>
#include <functional>
#include <memory>

#include "../units.h"
#include "../../include/rapidjson/document.h"

using std::string;
using std::function;
using std::shared_ptr;

using rapidjson::Value;

namespace mbc { namespace Val { // begin for namespace mbc::Val

// ----------------------------------------------------------------------------
// ---[ base function ]--------------------------------------------------------
// ----------------------------------------------------------------------------

// : init and folding

Str::Str() {
    value_           = new string();

    *vaild_checker_  = [](const string& str){return true;};
    *invaild_waring_ = "[invaild str]";
    *type_           = Type(STR);

    set("");
}


Str::Str(std::function<bool(const string&)> vaild_checker) : _ValAtom(){
    value_           = new string();

    *vaild_checker_  = vaild_checker;
    *invaild_waring_ = "[invaild str]";
    *type_           = Type(STR);

    set("");
}


Str::Str(const Str& other) : _ValAtom(other) {
    value_ = other.value_;
    vaild_checker_ = other.vaild_checker_;
    invaild_waring_ = other.invaild_waring_;
    type_ = other.type_;
}

Str::~Str() {
    if(*count_ == 1) {
        delete value_;
    }
}


// ----------------------------------------------------------------------------
// ---[ repr function ]--------------------------------------------------------
// ----------------------------------------------------------------------------

// : show self as a string

// return string if it is vaild (called by function str)
const string Str::str_() const {
    return units::repr(*value_);
}


// ----------------------------------------------------------------------------
// ---[ init function ]--------------------------------------------------------
// ----------------------------------------------------------------------------

// :init will new a pointer to string, and ~ will delete it

// init self as deafult (called by function set)
void Str::init_() {
    *value_ = string();
}


// init self by string
void Str::init_(const std::string& str) {
    *value_ = str;
}


_ValAtom& Str::reprset(const string& str) {
    string result = "";
    try {
        result = units::parse_str_repr(str);
    } catch (const units::bad_parser& e) {
        throw Val::bad_value();
    }
    if((*vaild_checker_)(result)) {
        *value_ = result;
    } else {
        *value_ = result;
    }
    return *this;
}

// ----------------------------------------------------------------------------
// ---[ interface method ]-----------------------------------------------------
// ----------------------------------------------------------------------------

// return self's string
const string& Str::raw() const {
    return *value_;
}


// return self's json value
shared_ptr<Value> Str::json_value() {
    shared_ptr<Value> v = std::make_shared<Value>();
    auto& allo = doc_.GetAllocator();

    v -> SetObject();
    v -> AddMember("valid", *is_vaild_, allo);
    v -> AddMember("value", Value(value_->c_str(), allo).Move(), allo);

    return v;
}


bool Str::operator<(const Str& other) {
    string this_string = this -> str() + this -> raw();
    string other_string = other.str()  + other.raw();
    return this_string < other_string;
};

}} // for namespace mbc::Val
