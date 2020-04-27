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

// Class Person
class Person {
public:
    Person();
    Person(std::string name, std::string sex, std::string telephone,
           std::string location, std::string mail_number, std::string email,
           std::string qq_number, Cls classes);
    Person(std::istream& in, std::ostream& out);

    void setID(std::string ID);
    std::string ID();
    std::string hash();
    void change(std::string key, std::string value);

    rapidjson::Value* get_rapidjson_value(rapidjson::Document::AllocatorType& allo);

    std::string str() const;
    friend std::ostream& operator<<(std::ostream& out, const Person& p);
private:
    void init(std::string name, std::string sex, std::string telephone,
              std::string location, std::string mail_number, std::string email,
              std::string qq_number, Cls classes);
    void init();

    std::string ID_;
    Value<std::string> name_;
    Value<std::string> sex_;
    Value<std::string> telephone_;
    Value<std::string> location_;
    Value<std::string> mail_number_;
    Value<std::string> email_;
    Value<std::string> qq_number_;
    Cls classes_;
};

std::ostream& operator<<(std::ostream& out, const Person& p);

#endif // for ifndef PETERLITS_PERSON_H__
