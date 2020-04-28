#include "idmap.h"

#include "../person_ptr.h"

using std::string;

string IdmapValue::str() {
    if(type == PERSON) {
        return value.p->str();
    } else {
        return *value.s;
    }
}

// ----------------------------------------------------------------------------

Idmap::Idmap() {
    ; // do nothing
}

IdmapValue& Idmap::operator[] (string key) {
    return idmap_[key];
}
