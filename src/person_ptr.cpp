#include "person_ptr.h"

#include <string>

#include "messagebook.h"

using std::string;

PersonPtr::PersonPtr(MessageBook& mb, string ID):mb_(mb), ID_(ID)
    {}

void PersonPtr::change(string key, string value) {
    if (ID_ != "") {
        auto person = mb_.get_raw(ID_);
        person.change(key, value);
        mb_.remove(ID_);
        mb_.addPerson(person);
        ID_ = person.ID();
    }
}

bool PersonPtr::remove() {
    if (ID_ != "") {
        mb_.remove(ID_);
        ID_ = "";
        return true;
    } else {
        return false;
    }
}

string PersonPtr::str() {
    if (ID_ != "") {
        auto person = mb_.get_raw(ID_);
        return person.str();
    } else {
        return "[NULL person]";
    }
}
