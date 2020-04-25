#ifndef PETERLITS_PERSON_H__
#define PETERLITS_PERSON_H__

#include <list>
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

// Class Classes
using Classes = std::vector<std::string>;

// Class Person
class Person {
public:
    Person();
    Person(string name, string sex, string telephone, string location,
           string mail_number, string email, string qq_number,
           Classes classes);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

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

std::ostream& operator<<(std::ostream& out, const Person& p);

#endif // for ifndef PETERLITS_PERSON_H__
