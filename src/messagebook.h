#ifndef PETERLITS_MEASSAGEBOOK_H
#define PETERLITS_MEASSAGEBOOK_H

#include <ostream>
#include <string>
#include <vector>
#include <iostream>
#include "person.h"
using std::string;
using std::vector;
using Classes = vector<string>;

class MessageBook {
public:
    MessageBook():lastID_(0) {};
    void addPerson(string name, string sex, string telephone, string location, 
                   string mail_number, string email, string qq_number, 
                   Classes classes);
    friend std::ostream& operator<<(std::ostream& out, const MessageBook& mb);

private:
    vector<Person> persons;
    int lastID_;
};

std::ostream& operator<<(std::ostream& out, const MessageBook& mb);

#endif // for ifndef PETERLITS_MEASSAGEBOOK_H
