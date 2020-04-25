#include "person.h"
#include <ostream>
#include <iostream>
#include <string>

#include "value.h"
#include "units.h"

using std::string;

Person::Person()
              : name_(Value<string>()), sex_(Value<string>()),
                telephone_(Value<string>()), location_(Value<string>()),
                mail_number_(Value<string>()), email_(Value<string>()),
                qq_number_(Value<string>()), classes_(Classes()) {}

Person::Person(string name, string sex, string telephone, string location,
               string mail_number, string email, string qq_number, Classes classes)
               : name_(name), location_(location), classes_(classes)
{
    // the sex's value should be one of "M", "F" or "unknown"
    if(sex == "M" || sex == "F") {
        sex_ = Str(sex);
    }
    // the telephone's value should be a string of digits: eg: "123456789"
    if(units::is_digit(telephone)) {
        telephone_ = Str(telephone);
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

std::ostream& operator<<(std::ostream& out, const Person& p) {
    // output the basic infomation
    out << " ┌- name: " << p.name_ << ", sex: " << p.sex_ << ", telephone: " << p.telephone_
        << ", mail-number: " << p.mail_number_ << '\n';
    out << " |  email: " << p.email_ << ", qq-number: " << p.qq_number_
        << ", location: " << p.location_ << '\n';
    out << " └- classes: ";
    // output its classes
    for(auto cls: p.classes_) {
        out << cls;
    }
    //output newline
    out << '\n';
    return out;
}
