#include "messagebook.h"

#include <ostream>
#include <string>
#include <iostream>

#include "person.h"

using std::string;

void MessageBook::addPerson(string name, string sex, string telephone, string location, 
                            string mail_number, string email, string qq_number, 
                            Classes classes) {
    Person person(name, sex, telephone, location, mail_number, email, qq_number, classes);
    persons.push_back(person);
}

std::ostream& operator<<(std::ostream& out, const MessageBook& mb) {
    for(auto person: mb.persons) {
        out << person;
        out << '\n';
    }
    return out;
}
