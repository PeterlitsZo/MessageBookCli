#include "val.h"

#include <string>
#include <functional>
#include <memory>

#include "units.h"
#include "../include/rapidjson/document.h"

using std::string;
using std::vector;
using std::function;
using std::shared_ptr;

using rapidjson::Value;

namespace mbc { namespace Val { // begin for namespace mbc::Val

// ----------------------------------------------------------------------------
// ---[ init and folding method ]----------------------------------------------
// ----------------------------------------------------------------------------

VecStr::VecStr() : _ValAtom() {
    value_          = new vector<string>();

    *vaild_checker_  = [](const string& str){return true;};
    *invaild_waring_ = "[invaild vecstr]";
    *type_           = Type(VECSTR);
    
    set("[]");
}


VecStr::VecStr(std::function<bool(const std::string&)> vaild_checker) : _ValAtom() {
    value_          = new vector<string>();

    *vaild_checker_  = vaild_checker;
    *invaild_waring_ = "[invaild vecstr]";
    *type_           = Type(VECSTR);

    set("[]");
}


VecStr::VecStr(const VecStr& other) : _ValAtom(other) {
    value_ = other.value_;
    vaild_checker_ = other.vaild_checker_;
    invaild_waring_ = other.invaild_waring_;
    type_ = other.type_;
}


VecStr::~VecStr() {
    if (*count_ == 1) {
        delete value_;
    }
}

// ----------------------------------------------------------------------------
// ---[ repr method ]----------------------------------------------------------
// ----------------------------------------------------------------------------

// return string if it is vaild (called by function str)
const string VecStr::str_() const {
    return units::repr(value_->cbegin(), value_->cend());
}

// ----------------------------------------------------------------------------
// ---[ init/reset method ]----------------------------------------------------
// ----------------------------------------------------------------------------

// init self as deafult (called by function set)
void VecStr::init_() {
    *value_ = vector<string>();
}

// init self by string
void VecStr::init_(const std::string& str) {
    try {
        *value_ = units::parse_vecstr_repr(str);
    } catch (const units::bad_parser& e) {
        throw Val::bad_value();
    }
}

// ----------------------------------------------------------------------------
// ---[ json method ]----------------------------------------------------------
// ----------------------------------------------------------------------------

// return self's json value
shared_ptr<Value> VecStr::json_value() {
    shared_ptr<Value> v = std::make_shared<Value>();
    auto& allo = doc_.GetAllocator();

    v -> SetObject();
    v -> AddMember("valid", *is_vaild_, allo);

    auto vv = new Value();
    vv -> SetArray();
    for (auto it = value_->begin(); it != value_->end(); ++it) {
        vv -> PushBack(Value(it->c_str(), allo).Move(), allo);
    }
    v -> AddMember("value", *vv, allo);
    delete vv;

    return v;
}


}} // for namespace mbc::Val
