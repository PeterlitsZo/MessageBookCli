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

VecStr::VecStr() {
    vaild_checker_  = [](const string& str){return true;};
    invaild_waring_ = std::make_shared<string>("[invaild vecstr]");
    value_          = std::make_shared<vecstr_Type>();
    type_           = Type::VECSTR;
    
    set("[]");
}

VecStr::VecStr(std::function<bool(const std::string&)> vaild_checker) {
    vaild_checker_  = vaild_checker;
    invaild_waring_ = std::make_shared<string>("[invaild vecstr]");
    value_          = std::make_shared<vecstr_Type>();
    type_           = Type::VECSTR;

    set("[]");
}


VecStr::~VecStr() {
    ; // do nothing
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
    *value_ = vecstr_Type();
}

// init self by string
void VecStr::init_(const std::string& str) {
    *value_ = units::parse_vecstr_repr(str);
}

// ----------------------------------------------------------------------------
// ---[ json method ]----------------------------------------------------------
// ----------------------------------------------------------------------------

// return self's json value
shared_ptr<Value> VecStr::json_value() {
    shared_ptr<Value> v(new Value());
    auto& allo = doc_.GetAllocator();

    v -> SetObject();
    v -> AddMember("valid", is_vaild_, allo);

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
