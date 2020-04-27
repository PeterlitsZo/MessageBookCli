#ifndef PETERLITS_MEASSAGEBOOK_H
#define PETERLITS_MEASSAGEBOOK_H

#include <ostream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "person.h"

class PersonPtr;

class MessageBook {
public:
    MessageBook(const char* path);

    void addPerson(std::string name, std::string sex, std::string telephone,
                   std::string location, std::string mail_number,
                   std::string email, std::string qq_number, 
                   std::vector<std::string> classes);
    void addPerson(std::istream& in, std::ostream& out);
    void addPerson(Person p);
    std::string addPerson(void);

    void remove(std::string ID);

    void save();
    Person& get_raw(std::string ID);
    PersonPtr get(std::string ID);

    std::string str() const;

    friend std::ostream& operator<<(std::ostream& out, const MessageBook& mb);

private:
    std::string getfullID(std::string ID);
    std::string path_;
    std::map<std::string, Person> persons;
};

std::ostream& operator<<(std::ostream& out, const MessageBook& mb);

#endif // for ifndef PETERLITS_MEASSAGEBOOK_H
