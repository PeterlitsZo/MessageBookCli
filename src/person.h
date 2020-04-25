#ifndef PETERLITS_PERSON_H__
#define PETERLITS_PERSON_H__

#include <list>
#include <string>
#include <vector>
using std::string;
using std::vector;
using Classes = std::vector<std::string>;

class Person {
public:
    Person();
    Person(string name, string sex, string telephone, string location,
           string mail_number, string email, string qq_number,
           Classes classes);

private:
    string name_;
    string sex_;
    string telephone_;
    string location_;
    string mail_number_;
    string email_;
    string qq_number_;
    Classes classes_;
};

#endif // for ifndef PETERLITS_PERSON_H__
