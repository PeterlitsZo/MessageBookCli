#ifndef PETERLITS_MEASSAGEBOOK_H
#define PETERLITS_MEASSAGEBOOK_H

#include <ostream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "person.h"

using std::string;
using std::vector;
using Classes = vector<string>;

class PersonPtr;

class MessageBook {
public:
    MessageBook(const char* path);

    void addPerson(string name, string sex, string telephone, string location, 
                   string mail_number, string email, string qq_number, 
                   Classes classes);
    void addPerson(std::istream& in, std::ostream& out);
    void addPerson(Person p);
    void remove(std::string ID);

    void save();
    Person& get_raw(std::string ID);
    PersonPtr get(std::string ID);

    friend std::ostream& operator<<(std::ostream& out, const MessageBook& mb);

private:
    std::string getfullID(std::string ID);
    string path_;
    std::map<std::string, Person> persons;
};

std::ostream& operator<<(std::ostream& out, const MessageBook& mb);

#endif // for ifndef PETERLITS_MEASSAGEBOOK_H
