#ifndef PETERLITS_PERSON_PTR__
#define PETERLITS_PERSON_PTR__

#include <string>

#include "messagebook.h"

class PersonPtr {
public:
    PersonPtr(MessageBook& mb, std::string str);

    void change(std::string key, std::string value);
    bool remove();

    std::string str();

private:
    MessageBook& mb_;
    std::string ID_;

};


#endif // for ifndef PETERLITS_PERSON_PTR__
