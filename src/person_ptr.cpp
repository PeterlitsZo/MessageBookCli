#include "person_ptr.h"

#include <string>

#include "messagebook.h"

using std::string;

PersonPtr::PersonPtr(MessageBook& mb, string ID):mb_(mb), ID_(ID)
    {}

void PersonPtr::change(string key, string value) {
    // TODO: ID change
    mb_.get_raw(ID_).change(key, value);
}
