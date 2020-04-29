#include "idmap.h"

#include <map>

#include "../person_ptr.h"
#include <pthread.h>

using std::string;

// string IdmapValue::str() {
//     if(type == PERSON) {
//         return value.p->str();
//     } else {
//         return *value.s;
//     }
// }


Val::Val (PersonPtr* ptr) {
    type_ = Val_T::PER;
    val_.p = ptr;
}

Val::Val (std::string* ptr) {
    type_ = Val_T::STR;
    val_.s = ptr;
}

Val::Val () {
    type_ = Val_T::NUL;
}

string Val::str() {
    if (type_ == Val_T::PER) {
        return val_.p -> str();
    } else if (type_ == Val_T::STR) {
        return *(val_.s);
    } else if (type_ == Val_T::NUL) {   
        return "nil";
    }
    return "[ [error] the type is not person or string ]";
}

PersonPtr* Val::getPersonPtr() {
    if (type_ == Val_T::PER) {
        return val_.p;
    } else {
        return nullptr;
    }
}

string* Val::getString() {
    if (type_ == Val_T::STR) {
        return val_.s;
    } else {
        return nullptr;
    }
}

void Val::del() {
    if (type_ == Val_T::PER ) {
        delete val_.p;
    } else if ( type_ == Val_T::STR ) {
        delete val_.s;
    }
}

// ----------------------------------------------------------------------------

Idmap::Idmap() {
    ; // do nothing
}

Idmap::~Idmap() {
    // clear all ptr of it
    for (auto it = idmap_.begin(); it != idmap_.end(); ++it) {
        (it -> second)->del();
        delete it -> second;
    }
}

void Idmap::update (string name, Val* value) {
    idmap_[name] = value;
}

Val* Idmap::get (string name) {
    if (idmap_.count(name)) {
        return idmap_[name];
    } else {
        return new Val();
    }
}

// Val& Idmap::operator[] (string key) {
//     return idmap_[key];
// }

