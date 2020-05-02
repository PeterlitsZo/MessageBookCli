#include "val.h"

#include <cstdio>
#include <string>
#include <functional>
#include <memory>
#include <exception>
#include <algorithm>

#include "units.h"
#include "../include/rapidjson/document.h"
#include "../include/logging/easylogging++.h"

using std::string;
using std::function;
using std::shared_ptr;

using rapidjson::Value;

namespace mbc { namespace Val { // begin for namespace mbc::Val

struct nojson : public std::exception {
    const char* what() throw() {
        return "should not get personhaneld's json Value";
    }
};

PersonHandle::PersonHandle(shared_ptr<MessageBook> mb, const string& full_ID) {
    mb_             = mb;
    invaild_waring_ = std::make_shared<string>("[person handle -> invaild person]");

    // reset person
    if (mb_ -> persons_ -> count(full_ID)) {
        is_vaild_       = true;
        person_         = std::make_shared<Person>((*(mb_ -> persons_))[full_ID]);
    } else {
        is_vaild_       = false;
        person_         = std::make_shared<Person>();
    }
}


PersonHandle::PersonHandle(const PersonHandle& personhandle) {
    mb_ = personhandle.mb_;
    invaild_waring_ = personhandle.invaild_waring_;

    is_vaild_ = personhandle.is_vaild_;
    person_ = personhandle.person_;
}


PersonHandle::~PersonHandle() {
    ; // do nothing
}

void PersonHandle::reset_() {
    // if person is vaild and mb_ has it, then it is vaild.
    if(person_ -> ID().vaild() && mb_ -> persons_ -> count(person_ -> ID().raw()) ) {
        is_vaild_ = true;
    } else {
        is_vaild_ = false;
    }
}

PersonHandle& PersonHandle::remove() {
    reset_();
    if(is_vaild_) {
        auto it_persons = mb_ -> persons_ -> find(person_ -> ID().raw());
        auto it_order = std::find(mb_->order_->begin(), mb_->order_->end(), 
                                 (person_ -> ID().raw()));
        mb_ -> persons_ -> erase(it_persons);
        mb_ -> order_ -> erase(it_order);
        is_vaild_ = false;
        mb_ -> save();
    } else {
        ; // do nothing
    }
    return *this;
}

PersonHandle& PersonHandle::changeAttr(string attribute, string value) {
    reset_();
    if(is_vaild_) {
        // after the person's ID is changed, update mb.
        remove();
        auto attr = person_ -> attr(attribute);
        if(attr -> type() == mbc::Val::Type::STR) {
            Str* temp = (Str*) attr;
            temp -> set(value);
        } else {
            VecStr* temp = (VecStr*) attr;
            temp -> set(value);
        }
        person_ -> update_ID_();
        (*(mb_ -> persons_))[person_ -> ID().raw()] = *person_;
        mb_ -> order_ -> push_back(person_ -> ID().raw());
        is_vaild_ = true;

        mb_ -> save();
    } else {
        ; // do nothing
    }
    return *this;
}

// return string if it is vaild (called by function str)
const string PersonHandle::str_() const {
    return "[person handle -> ]\n" + units::add_head(person_ -> str(), "  ");
}

// return self's json value
shared_ptr<Value> PersonHandle::json_value() {
    throw nojson();
}


}} // for namespace mbc::Val
