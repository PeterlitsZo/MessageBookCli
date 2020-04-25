#include "messagebook.h"

#include <string>

#include "person.h"

using std::string;

void MessageBook::addPerson(string name, string sex, string telephone, string location, 
                            string mail_number, string email, string qq_number, 
                            Classes classes) {
    Person person(name, sex, telephone, location, mail_number, email, qq_number, classes);
    persons.push_back(person);
}

