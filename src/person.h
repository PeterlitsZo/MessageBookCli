#ifndef PETERLITS_PERSON_H__
#define PETERLITS_PERSON_H__

#include <list>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

// for json object;
#include "../include/rapidjson/document.h"

#include "classes.h"
#include "value.h"

using std::string;
using std::vector;

// Class Classes
using Str  = Value<std::string>;
using Int  = Value<int>;

// Class Person
class Person {
public:
    Person();
    Person(string name, string sex, string telephone, string location,
           string mail_number, string email, string qq_number,
           Cls classes);
    Person(std::istream& in, std::ostream& out);

    void setID(string ID);
    std::string ID();
    std::string hash();
    void change(std::string key, std::string value);

    rapidjson::Value* get_rapidjson_value(rapidjson::Document::AllocatorType& allo);

    std::string str() const;
    friend std::ostream& operator<<(std::ostream& out, const Person& p);
private:
    void init(string name, string sex, string telephone, string location,
              string mail_number, string email, string qq_number, Cls classes);
    void init();

    string ID_;
    Str name_;
    Str sex_;
    Str telephone_;
    Str location_;
    Str mail_number_;
    Str email_;
    Str qq_number_;
    Cls classes_;
};

std::ostream& operator<<(std::ostream& out, const Person& p);

#endif // for ifndef PETERLITS_PERSON_H__
