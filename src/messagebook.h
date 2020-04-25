#include <string>
#include <vector>
#include "person.h"
using std::string;
using std::vector;
using Classes = vector<string>;

class MessageBook {
public:
    void addPerson(string name, string sex, string telephone, string location, 
                   string mail_number, string email, string qq_number, 
                   Classes classes);

private:
    vector<Person> persons;
};
