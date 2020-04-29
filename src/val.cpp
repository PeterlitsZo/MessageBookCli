#include "val.h"

#include <string>

#include "../include/rapidjson/document.h"
#include <type_traits>

#include "units.h"

using std::string;
using std::vector;

using rapidjson::Value;
using rapidjson::Document;

namespace mbc {

// ----------------------------------------------------------------------------
// ---[ ValBase ]--------------------------------------------------------------
// ----------------------------------------------------------------------------

ValBase::ValBase(Document::AllocatorType& allocator)
    : json_allocator_(allocator), is_vaild_(false)
    {}

namespace Val {

// ----------------------------------------------------------------------------
// ---[ Val::Str ]-------------------------------------------------------------
// ----------------------------------------------------------------------------

Str::Str(Document::AllocatorType& allocator)
    : ValBase(allocator)
    { }

Str::Str(Document::AllocatorType& allocator, string str)
    : ValBase(allocator)
    { is_vaild_ = true; value_ = &str; }

string Str::str() {
    if (is_vaild_) {
        auto value = *value_;
        return units::repr(value);
    } else {
        return "[invaild]";
    }
}

Value* Str::get_json_value() {
    auto value = new Value();
    value -> SetObject();

    value -> AddMember("valid", is_vaild_, json_allocator_);
    value -> AddMember("value",
                       Value(value_ -> c_str(), json_allocator_).Move(),
                       json_allocator_);

    return value;
}

// ----------------------------------------------------------------------------
// ---[ Val::VecStr ]----------------------------------------------------------
// ----------------------------------------------------------------------------

VecStr::VecStr(Document::AllocatorType& allocator)
    : ValBase(allocator)
    { is_vaild_ = true; } // even thourg it is empty vec, it is also vaild

VecStr::VecStr(Document::AllocatorType& allocator, vector<string> vecstr)
    : ValBase(allocator)
    { is_vaild_ = true; value_ = &vecstr; }

string VecStr::str() {
    if (is_vaild_) {
        auto value = *value_;
        return units::repr(value.cbegin(), value.cend());
    } else {
        return "[invaild]";
    }
}

Value* VecStr::get_json_value() {
    auto value = new Value();
    value -> SetObject();

    value -> AddMember("valid", is_vaild_, json_allocator_);

    // json value(Value*) for value(vector<>*)
    auto value_value = new Value();
    value_value -> SetArray();

    for (auto it = value_->begin(); it != value_->end(); ++it) {
        value_value -> PushBack(Value(it->c_str(), json_allocator_).Move(),
                                json_allocator_);
    }
    value -> AddMember("value", *value_value, json_allocator_);
    delete value_value;

    return value;
}

} // for namespace Val

} // for namespace mbc
