#include "person.h"

#include <ostream>
#include <iostream>
#include <string>

// for read and write json file
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/writer.h"

// for hash
#include "../include/digestpp/digestpp.hpp"

#include "value.h"
#include "units.h"
#include "classes.h"

using std::string;

// ----------------------------------------------------------------------------
// ---[ initialy the object ]--------------------------------------------------
// ----------------------------------------------------------------------------

// initialy as default.
Person::Person()
              : name_(Value<string>()), sex_(Value<string>()),
                telephone_(Value<string>()), location_(Value<string>()),
                mail_number_(Value<string>()), email_(Value<string>()),
                qq_number_(Value<string>()), classes_(Cls()) {}

// initialy with a lot of argrument
Person::Person(string name, string sex, string telephone, string location,
               string mail_number, string email, string qq_number,
               Cls classes): classes_(classes)
{
    // the name's value should not be a empty string
    if(units::is_not_empty(name)) {
        name_ = name;
    }
    // the sex's value should be one of "M", "F" or "unknown"
    if(sex == "M" || sex == "F") {
        sex_ = Str(sex);
    }
    // the telephone's value should be a string of digits: eg: "123456789"
    if(units::is_digit(telephone)) {
        telephone_ = Str(telephone);
    }
    // the location's value should not be a empty string
    if(units::is_not_empty(location)) {
        location_ = location;
    }
    // the mail_number should be a 6-length of a digit string: eg: "123456"
    if(units::is_digit(mail_number) && mail_number.size() == 6) {
        mail_number_ = Str(mail_number);
    }
    // the qq-number's value should be a string of digits: eg: "123456789"
    if(units::is_digit(qq_number)) {
        qq_number_ = Str(qq_number);
    }
    // the email should have the format like: "abc@abc.abc"
    if(units::is_email(email)) {
        email_ = Str(email);
    }

}

// ----------------------------------------------------------------------------
// ---[ normal method ]--------------------------------------------------------
// ----------------------------------------------------------------------------

void Person::setID(string ID) {
    ID_ = ID;
}

// [WARNING]: remember to delete it! (should I?)
rapidjson::Value* Person::get_rapidjson_value(rapidjson::Document::AllocatorType& allo) {
    // initial as a Null Object
    rapidjson::Value* v = new rapidjson::Value();
    v->SetObject();

    // objter V
    // v->AddMember("ID",          *ID_.get_rapidjson_value( allo ),          allo);
    v->AddMember("name",        *name_.get_rapidjson_value( allo ),        allo);
    v->AddMember("sex",         *sex_.get_rapidjson_value( allo ),         allo);
    v->AddMember("telephone",   *telephone_.get_rapidjson_value( allo ),   allo);
    v->AddMember("mail_number", *mail_number_.get_rapidjson_value( allo ), allo);
    v->AddMember("email",       *email_.get_rapidjson_value( allo ),       allo);
    v->AddMember("qq_number",   *qq_number_.get_rapidjson_value( allo ),   allo);
    v->AddMember("location",    *location_.get_rapidjson_value( allo ),    allo);
    // TODO: classes

    // return the pointer
    return v;
}

string Person::hash() {
    using rapidjson::StringBuffer;
    using rapidjson::Writer;
    using rapidjson::Document;
    using digestpp::md5;

    Document doc;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    get_rapidjson_value(doc.GetAllocator())->Accept(writer);

    return md5().absorb(buffer.GetString()).hexdigest();
}

// ----------------------------------------------------------------------------
// ---[ friend function ]------------------------------------------------------
// ----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& out, const Person& p) {
    // output the basic infomation
    out << " ┌-----| ID: " << p.ID_    << " |-------"         << '\n';
    out << " | name: "              << p.name_           <<
               ", sex: "            << p.sex_            <<
               ", telephone: "      << p.telephone_      <<
               ", mail-number: "    << p.mail_number_    << '\n';
    out << " | email: "             << p.email_          <<
               ", qq-number: "      << p.qq_number_      <<
               ", location: "       << p.location_       << '\n';
    out << " └ classes: "           << p.classes_        << '\n';
    return out;
}
