#include "messagebook.h"
#include "person.h"
#include <cstdlib>

void MessageBook::addPerson(string name, string sex, string telephone, string location,
                            string mail_number, string email, string qq_number,
                            Classes classes)
{
    auto p = Person(name, sex, telephone, location, mail_number,
                    email, qq_number, classes);
    persons.push_back(p);
}
