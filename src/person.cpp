#include "person.h"
#include "units.h"
#include "units.h"
#include <ostream>
#include <iostream>

Person::Person()
              : name_("unknown"), sex_("unknown"), telephone_("unkonwn"),
                location_("unknown"), mail_number_("unknown"), email_("unknown"),
                qq_number_("unknown"), classes_(Classes()) {}

Person::Person(string name, string sex, string telephone, string location, 
               string mail_number, string email, string qq_number,
               Classes classes)
               : name_(name), location_(location), classes_(classes)
{
    // the sex's value should be one of "M", "F" or "unknown"
    if(sex == "M" || sex == "F") {
        sex_ = sex;
    }
    // the telephone's value should be a string of digits: eg: "123456789"
    if(units::is_digit(telephone)) {
        telephone_ = telephone;
    }
    // the mail_number should be a 6-length of a digit string: eg: "123456"
    if(units::is_digit(mail_number) && mail_number.size() == 6) {
        mail_number_ = mail_number;
    }
    // the qq-number's value should be a string of digits: eg: "123456789"
    if(units::is_digit(qq_number)) {
        qq_number_ = qq_number;
    }
    // the email should have the format like: "abc@abc.abc"
    if(units::is_email(email)) {
        email_ = email;
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
