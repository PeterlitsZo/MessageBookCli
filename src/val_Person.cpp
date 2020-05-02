#include "val.h"

#include <linux/limits.h>
#include <string>
#include <functional>
#include <memory>
#include <exception>

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/writer.h"

#define FMT_HEADER_ONLY
#include "../include/fmt/format.h"

#include "../include/logging/easylogging++.h"

#include "units.h"

using std::string;
using std::function;
using std::shared_ptr;

using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::StringBuffer;

namespace mbc { namespace Val { // begin for namespace mbc::Val

struct bad_attr : public std::exception {
    const char* what() throw() {
        return "the attribute is unused";
    }
};

Person::Person() {
    using namespace units;
    auto& parse = parse_str_repr;

    is_vaild_       = true;
    invaild_waring_ = std::make_shared<string>("[invaild person]");

    ID_             = Str([](const string& str){return is_not_empty(parse(str));});
    name_           = Str([](const string& str){return is_not_empty(parse(str));});
    sex_            = Str([](const string& str){return str == "M" || str == "F";});
    telephone_      = Str([](const string& str){return is_digit(parse(str));});
    mail_number_    = Str([](const string& str){
                            return is_digit(parse(str)) && parse(str).size() == 6;
                            });
    email_          = Str([](const string& str){return is_email(parse(str));});
    qq_number_      = Str([](const string& str){return is_digit(parse(str));});
    location_       = Str([](const string& str){return is_not_empty(parse(str));});

    classes_        = VecStr();

    update_ID_();
}

Person::Person(const Person& person) {
    using namespace units;

    is_vaild_       = true;
    invaild_waring_ = person.invaild_waring_;
    ID_             = person.ID_;
    name_           = person.name_;
    sex_            = person.sex_;
    telephone_      = person.telephone_;
    mail_number_    = person.mail_number_;
    email_          = person.email_;
    qq_number_      = person.qq_number_;
    location_       = person.location_;
    classes_        = person.classes_;
}

Person::~Person() {
    ; // do nothing
}


void Person::update_ID_() {
    ID_.set(string("\"") + hash_() + "\"");
}

const Str& Person::ID() const {
    return ID_;
}

// return string if it is vaild (called by function str)
const string Person::str_() const {
    return fmt::format(
        "┌------| id: {} |------\n{}",
        // ┌——————————^           ^
        // |(id)                  │
        ID_.str(),             // │(body)
        units::add_head( units::hard_warp( fmt::format(
            "name: {}, sex: {}, telephone: {}, mail_number: {}, email: {},"
            "qq_number: {}, location: {}, classes: {}", 
            name_.str(), sex_.str(), telephone_.str(), mail_number_.str(),
            email_.str(), qq_number_.str(), location_.str(), classes_.str()
        ), 80), "| ")
        // ^------------------ hard wrap width
        //      ^------------- every line's head
    );
}


string Person::hash_() {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json_value() -> Accept(writer);
    return units::md5(buffer.GetString());
}

// get the attr of person
_ValAtom* Person::attr(string attribute) {
    if(attribute == "name")             return &name_;
    if(attribute == "sex")              return &sex_;
    if(attribute == "telephone")        return &telephone_;
    if(attribute == "mail_number")      return &mail_number_;
    if(attribute == "email")            return &email_;
    if(attribute == "qq_number")        return &qq_number_;
    if(attribute == "location")         return &location_;
    if(attribute == "classes")          return &classes_;

    throw bad_attr();
}


// return self's json value
shared_ptr<Value> Person::json_value() {
    shared_ptr<Value> v(new Value());
    auto& allo = doc_.GetAllocator();

    v -> SetObject();
    v -> AddMember("name",          *name_.json_value(),        allo);
    v -> AddMember("sex",           *sex_.json_value(),         allo);
    v -> AddMember("telephone",     *telephone_.json_value(),   allo);
    v -> AddMember("mail_number",   *mail_number_.json_value(), allo);
    v -> AddMember("email",         *email_.json_value(),       allo);
    v -> AddMember("qq_number",     *qq_number_.json_value(),   allo);
    v -> AddMember("location",      *location_.json_value(),    allo);
    v -> AddMember("classes",       *classes_.json_value(),     allo);

    return v;
}


}} // for namespace mbc::Val
