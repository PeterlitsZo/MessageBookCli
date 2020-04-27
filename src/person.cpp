#include "person.h"

#include <bits/pthreadtypes-arch.h>
#include <cstdarg>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>

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
using std::istream;
using std::ostream;

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

// ----------------------------------------------------------------------------
// ---[ initialy the object ]--------------------------------------------------
// ----------------------------------------------------------------------------

// initialy with a lot of argrument
void Person::init(string name, string sex, string telephone, string location,
                  string mail_number, string email, string qq_number,
                  Cls classes)
{
    if(vaild_name(name))               name_ = name;
    if(vaild_sex(sex))                 sex_ = Str(sex);
    if(vaild_telephone(telephone))     telephone_ = Str(telephone);
    if(vaild_locaition(location))      location_ = location;
    if(vaild_mail_number(mail_number)) mail_number_ = Str(mail_number);
    if(vaild_qq_number(qq_number))     qq_number_ = Str(qq_number);
    if(vaild_email(email))             email_ = Str(email);

    classes_ = classes;
    ID_ = hash();
}

// initialy with empty argument
void Person::init()
{
    ID_ = hash();
}

// initialy as default.
Person::Person() {
    init();
}

// initialy with a lot of argrument
Person::Person(string name, string sex, string telephone, string location,
               string mail_number, string email, string qq_number,
               Cls classes)
{
    init(name, sex, telephone, location, mail_number, email, qq_number,
         classes);
}

Person::Person(istream& in, ostream& out) {
    units::Input input(in, out);
    string name, sex, telephone, location, mail_number, email, qq_number, temp;
    Cls classes;

    input("please enter name") >> name;
    input("please enter sex [M/F]") >> sex;;
    input("please enter telephone [only include digit]") >> telephone;
    input("please enter location") >> location;
    input("please enter postal number [6-length number]") >> mail_number;
    input("please enter email") >> email;
    input("please enter qq number") >> qq_number;
    input("please enter classes") >> classes;

    init(
        name, sex, telephone, location, mail_number, email, qq_number, classes
    );
}

// ----------------------------------------------------------------------------
// ---[ normal method ]--------------------------------------------------------
// ----------------------------------------------------------------------------

void Person::setID(string ID) {
    ID_ = ID;
}

string Person::ID() {
    return ID_;
}

void Person::change(string key, string value) {
    if(key == "name")
        name_ =        vaild_name(value) ? value: Str();
    else if(key == "sex")
        sex_ =         vaild_sex(value) ? value: Str();
    else if(key == "telephone")
        telephone_ =   vaild_telephone(value) ? value: Str();
    else if(key == "mail_number")
        mail_number_ = vaild_mail_number(value) ? value: Str();
    else if(key == "email")
        email_ =       vaild_email(value) ? value: Str();
    else if(key == "qq_number")
        qq_number_ =   vaild_qq_number(value) ? value: Str();
    else if(key == "location")
        location_ =    vaild_locaition(value) ? value: Str();
    else if(key == "classes")
        classes_ =     Cls(value);

    ID_ = hash();
    // ELSE: raise error
}

// [WARNING]: remember to delete it! (should I?)
rapidjson::Value* Person::get_rapidjson_value(rapidjson::Document::AllocatorType& allo) {
    // initial as a Null Object
    rapidjson::Value* v = new rapidjson::Value();
    v->SetObject();

    // objter V
    auto name_obj        = name_.get_rapidjson_value( allo );
    auto sex_obj         = sex_.get_rapidjson_value( allo );
    auto telephone_obj   = telephone_.get_rapidjson_value( allo );
    auto mail_number_obj = mail_number_.get_rapidjson_value( allo );
    auto email_obj       = email_.get_rapidjson_value( allo );
    auto qq_number_obj   = qq_number_.get_rapidjson_value( allo );
    auto location_obj    = location_.get_rapidjson_value( allo );
    auto classes_obj     = classes_.get_rapidjson_value( allo );

    v->AddMember("name",        *name_obj,        allo);
    v->AddMember("sex",         *sex_obj,         allo);
    v->AddMember("telephone",   *telephone_obj,   allo);
    v->AddMember("mail_number", *mail_number_obj, allo);
    v->AddMember("email",       *email_obj,       allo);
    v->AddMember("qq_number",   *qq_number_obj,   allo);
    v->AddMember("location",    *location_obj,    allo);
    v->AddMember("classes",     *classes_obj,     allo);

    delete name_obj;
    delete sex_obj;
    delete telephone_obj;
    delete mail_number_obj;
    delete email_obj;
    delete qq_number_obj;
    delete location_obj;
    delete classes_obj;

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
    // auto value = get_rapidjson_value(doc.GetAllocator());
    // value->Accept(writer);
    // delete value;
    get_rapidjson_value(doc.GetAllocator())->Accept(writer);

    return md5().absorb(buffer.GetString()).hexdigest();
}

// ----------------------------------------------------------------------------
// ---[ friend function ]------------------------------------------------------
// ----------------------------------------------------------------------------

string Person::str() const {
    using units::repr;
    string result;
    result += " ┌-----| id: "   + repr(ID_) + " |-------"
           +  '\n';
    result += " | name: "       + repr(name_)
           +  ", sex: "         + repr(sex_)
           +  ", telephone: "   + repr(telephone_)
           +  ", mail-number: " + repr(mail_number_)
           +  '\n';
    result += " | email: "      + repr(email_)
           +  ", qq-number: "   + repr(qq_number_)
           +  ", location: "    + repr(location_)
           +  '\n';
    result += " └ classes: "    + repr(classes_)
           +  '\n';
    return result;
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
    // output the basic infomation
    // out << " ┌-----| id: " << p.ID_ << " |-------"       << '\n';
    // out << " | name: "              << p.name_           <<
    //            ", sex: "            << p.sex_            <<
    //            ", telephone: "      << p.telephone_      <<
    //            ", mail-number: "    << p.mail_number_    << '\n';
    // out << " | email: "             << p.email_          <<
    //            ", qq-number: "      << p.qq_number_      <<
    //            ", location: "       << p.location_       << '\n';
    // out << " └ classes: "           << p.classes_        << '\n';
    out << p.str();
    return out;
}
