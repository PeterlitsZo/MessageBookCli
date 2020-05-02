#include "val.h"

#include <string>
#include <functional>
#include <memory>

#include "units.h"
#include "../include/rapidjson/document.h"
#include "../include/logging/easylogging++.h"

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
    vaild_checker_  = [](const string& str){return true;};
    invaild_waring_ = std::make_shared<string>("[invaild str]");
    value_          = std::make_shared<string>();
    type_           = Type::STR;

    set("\'\'");
}


Str::Str(std::function<bool(const string&)> vaild_checker) {
    vaild_checker_  = vaild_checker;
    invaild_waring_ = std::make_shared<string>("[invaild str]");
    value_          = std::make_shared<string>();
    type_           = Type::STR;

    set("\'\'");
}


Str::~Str() {
    ; // do nothing because it is shared_ptr
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
    *value_ = units::parse_str_repr(str);
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
    shared_ptr<Value> v(new Value());
    auto& allo = doc_.GetAllocator();

    v -> SetObject();
    v -> AddMember("valid", is_vaild_, allo);
    v -> AddMember("value", Value(value_->c_str(), allo).Move(), allo);

    return v;
}


}} // for namespace mbc::Val
