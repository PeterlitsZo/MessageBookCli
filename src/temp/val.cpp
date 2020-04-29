#include "val.h"

#include <string>

#include "../include/rapidjson/document.h"
#include "../include/digestpp/digestpp.hpp"
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

// init function for ValBase
ValBase::ValBase(Document::AllocatorType& allocator)
    : json_allocator_(allocator), is_vaild_(false)
    {}

namespace Val {

// ----------------------------------------------------------------------------
// ---[ Val::Str ]-------------------------------------------------------------
// ----------------------------------------------------------------------------

// init function for Val::Str
Str::Str(Document::AllocatorType& allocator)
    : ValBase(allocator)
    { }

Str::Str(Document::AllocatorType& allocator, string str)
    : ValBase(allocator)
    { is_vaild_ = true; value_ = &str; }

void Str::set(const Str& str) {
    value_ = str.value_;
}

// the string form for Val::Str
string Str::str() {
    if (is_vaild_) {
        auto value = *value_;
        return units::repr(value);
    } else {
        return "[invaild]";
    }
}

// the json::Value* form for Val::Str
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

// init function for Val::VecStr
VecStr::VecStr(Document::AllocatorType& allocator) : ValBase(allocator)
    { is_vaild_ = true; } // even thourg it is empty vec, it is also vaild

VecStr::VecStr(Document::AllocatorType& allocator, vector<string> vecstr)
    : ValBase(allocator)
    { is_vaild_ = true; value_ = &vecstr; }

VecStr::VecStr(Document::AllocatorType& allocator, string str)
    : ValBase(allocator){

    is_vaild_ = true;
    auto list_str = units::split(str);
    value_ -> insert(value_->end(), list_str.begin(), list_str.end());
}

void VecStr::set(const VecStr& str) {
    value_ = str.value_;
}

// the string form for Val::VecStr
string VecStr::str() {
    if (is_vaild_) {
        auto value = *value_;
        return units::repr(value.cbegin(), value.cend());
    } else {
        return "[invaild]";
    }
}

// the json::Value* form for Val::VecStr
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

// ----------------------------------------------------------------------------
// ---[ Val::Person ]----------------------------------------------------------
// ----------------------------------------------------------------------------

// ---[ units function ]-------------------------------------------------------

// the name's value should not be a empty string
bool vaild_name(string name) {return units::is_not_empty(name);}

// the sex's value should be one of "M", "F" or "unknown"
bool vaild_sex(string sex) {return (sex == "M" || sex == "F");}

// the telephone's value should be a string of digits: eg: "123456789"
bool vaild_telephone(string telephone) {return units::is_digit(telephone);}

// the location's value should not be a empty string
bool vaild_locaition(string location) {return units::is_not_empty(location);}

// the mail_number should be a 6-length of a digit string: eg: "123456"
bool vaild_mail_number(string mail_number) {
    return units::is_digit(mail_number) && mail_number.size() == 6;
}

// the qq-number's value should be a string of digits: eg: "123456789"
bool vaild_qq_number(string qq_number) {return units::is_digit(qq_number);}

// the email should have the format like: "abc@abc.abc"
bool vaild_email(string email) {return units::is_email(email);}

// initialy with a lot of argrument
void Person::init(string name, string sex, string telephone, string location,
                  string mail_number, string email, string qq_number,
                  string classes)
{
    if(vaild_name(name))               name_ = Str(json_allocator_, name);
    if(vaild_sex(sex))                 sex_ = Str(json_allocator_, sex);
    if(vaild_telephone(telephone))     telephone_ = Str(json_allocator_, telephone);
    if(vaild_locaition(location))      location_ = Str(json_allocator_, location);
    if(vaild_mail_number(mail_number)) mail_number_ = Str(json_allocator_, mail_number);
    if(vaild_qq_number(qq_number))     qq_number_ = Str(json_allocator_, qq_number);
    if(vaild_email(email))             email_ = Str(json_allocator_, email);

    classes_ = VecStr(json_allocator_, classes);
    ID_ = Str(json_allocator_, hash());
    is_vaild_ = true;
}

Person::Person(Document::AllocatorType& allocator) : ValBase(allocator) {
}

} // for namespace Val

} // for namespace mbc
