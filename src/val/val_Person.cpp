#include "val.h"

#include <string>
#include <functional>
#include <memory>
#include <exception>

#include "../../include/rapidjson/document.h"
#include "../../include/rapidjson/stringbuffer.h"
#include "../../include/rapidjson/writer.h"

#define FMT_HEADER_ONLY
#include "../../include/fmt/format.h"

#include "../units.h"

using std::string;
using std::function;
using std::shared_ptr;

using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::StringBuffer;

namespace mbc { namespace Val { // begin for namespace mbc::Val

Person::Person() : ValBase() {
    using namespace units;

    *is_vaild_       = true;
    *invaild_waring_ = "[invaild person]";

    ID_             = new Str([](const string& str){return is_not_empty(str);});
    name_           = new Str([](const string& str){return is_not_empty(str);});
    sex_            = new Str([](const string& str){return str == "M" || str == "F";});
    telephone_      = new Str([](const string& str){return is_digit(str);});
    mail_number_    = new Str([](const string& str){
                            return is_digit(str) && str.size() == 6;
                            });
    email_          = new Str([](const string& str){return is_email(str);});
    qq_number_      = new Str([](const string& str){return is_digit(str);});
    location_       = new Str([](const string& str){return is_not_empty(str);});

    classes_        = new VecStr();

    update_ID_();
}

Person::Person(const Person& other) : ValBase(other) {
    ID_             = other.ID_;
    name_           = other.name_;
    sex_            = other.sex_;
    telephone_      = other.telephone_;
    mail_number_    = other.mail_number_;
    email_          = other.email_;
    qq_number_      = other.qq_number_;
    location_       = other.location_;
    classes_        = other.classes_;

    is_vaild_       = other.is_vaild_;
    invaild_waring_ = other.invaild_waring_;
}

Person::~Person() {
    if (*count_ == 1) {
        delete ID_;
        delete name_;
        delete sex_;
        delete telephone_;
        delete mail_number_;
        delete email_;
        delete qq_number_;
        delete location_;
        delete classes_;
    }
}


void Person::update_ID_() {
    ID_ -> set(hash_());
}

const Str& Person::ID() const {
    return *ID_;
}

// return string if it is vaild (called by function str)
const string Person::str_() const {
    return fmt::format(
        "┌------| id: {} |------\n{}",
        // ┌——————————^           ^
        // |(id)                  │
        ID_->str(),             // │(body)
        units::add_head( units::hard_warp( fmt::format(
            "name: {}, sex: {}, telephone: {}, mail_number: {}, email: {},"
            "qq_number: {}, location: {}, classes: {}", 
            name_->str(), sex_->str(), telephone_->str(), mail_number_->str(),
            email_->str(), qq_number_->str(), location_->str(), classes_->str()
        ), 80), "| ")
        // ^------------------ hard wrap width
        //      ^------------- every line's head
    );
}

// return string if it is vaild (called by function str)
const string Person::str_width(int width) const {
    if (*is_vaild_) {
        return fmt::format(
            "┌------| id: {} |------\n{}",
            // ┌——————————^           ^
            // |(id)                  │
            ID_->str(),             // │(body)
            units::add_head( units::hard_warp( fmt::format(
                "name: {}, sex: {}, telephone: {}, mail_number: {}, email: {},"
                "qq_number: {}, location: {}, classes: {}", 
                name_->str(), sex_->str(), telephone_->str(), mail_number_->str(),
                email_->str(), qq_number_->str(), location_->str(), classes_->str()
            ), width), "| ")
            // ^------------------ hard wrap width
            //      ^------------- every line's head
        );
    } else {
        return *invaild_waring_;
    }
}

string Person::hash_() {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    // why I should add a prefix?
    Person::json_value() -> Accept(writer);
    return units::md5(buffer.GetString());
}

// get the attr of person
_ValAtom* Person::attr(string attribute) {
    if(attribute == "name")             return name_;
    if(attribute == "sex")              return sex_;
    if(attribute == "telephone")        return telephone_;
    if(attribute == "location")         return location_;
    if(attribute == "mail_number")      return mail_number_;
    if(attribute == "email")            return email_;
    if(attribute == "qq_number")        return qq_number_;
    if(attribute == "classes")          return classes_;

    throw bad_attr();
}


// return self's json value
shared_ptr<Value> Person::json_value() {
    shared_ptr<Value> v = std::make_shared<Value>();
    auto& allo = doc_.GetAllocator();

    v -> SetObject();
    v -> AddMember("name",        name_->json_value()        -> Move(), allo);
    v -> AddMember("sex",         sex_->json_value()         -> Move(), allo);
    v -> AddMember("telephone",   telephone_->json_value()   -> Move(), allo);
    v -> AddMember("location",    location_->json_value()    -> Move(), allo);
    v -> AddMember("mail_number", mail_number_->json_value() -> Move(), allo);
    v -> AddMember("email",       email_->json_value()       -> Move(), allo);
    v -> AddMember("qq_number",   qq_number_->json_value()   -> Move(), allo);
    v -> AddMember("classes",     classes_->json_value()     -> Move(), allo);

    return v;
}


}} // for namespace mbc::Val
