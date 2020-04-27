#include "person_ptr.h"

#include <string>

#include "messagebook.h"

using std::string;

PersonPtr::PersonPtr(MessageBook& mb, string ID):mb_(mb), ID_(ID)
    {}

void PersonPtr::change(string key, string value) {
    auto person = mb_.get_raw(ID_);
    person.change(key, value);
    mb_.remove(ID_);
    mb_.addPerson(person);
    ID_ = person.ID();
}

void PersonPtr::remove() {
    mb_.remove(ID_);
    ID_ = "";
}

string PersonPtr::str() {
    auto person = mb_.get_raw(ID_);
    return person.str();
}
