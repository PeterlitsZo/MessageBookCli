#include "val.h"

#include <cstdio>
#include <string>
#include <functional>
#include <memory>
#include <exception>
#include <algorithm>

#include "../units.h"
#include "../../include/rapidjson/document.h"

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

PersonHandle::PersonHandle(MessageBook* mb, Person* person) {
    mb_             = mb;
    person_         = person;
    *type_          = Type(PERSONHANDLE);
    *invaild_waring_ = "[person handle -> invaild person]";

    ++ *(mb_ -> count_);
    ++ *(person_ -> count_);

    reset_();
}


PersonHandle::PersonHandle(const PersonHandle& other) : ValBase(other) {
    mb_ = other.mb_;
    person_ = other.person_;

    ++ *(mb_ -> count_);
    ++ *(person_ -> count_);
}


PersonHandle::~PersonHandle() {
    -- *(mb_ -> count_);
    -- *(person_ -> count_);
}

void PersonHandle::reset_() {
    // if person is vaild and mb_ has it, then it is vaild.
    if(person_->ID() && mb_->persons_->count(person_->ID().raw()) ) {
        *is_vaild_ = true;
    } else {
        *is_vaild_ = false;
    }
}

PersonHandle& PersonHandle::remove() {
    if(*is_vaild_) {
        // remove self in mb_ -> persons_
        auto it_persons = mb_ -> persons_ -> find(person_ -> ID().raw());
        mb_ -> persons_ -> erase(it_persons);

        // remove self in mb_ -> order_
        auto it_order = std::find(mb_->order_->begin(), mb_->order_->end(), 
                                 person_ -> ID().raw() );
        mb_ -> order_ -> erase(it_order);

        // save messagebook and reset self, now it is unvaild
        mb_ -> save();
        reset_();
    } else {
        ; // do nothing
    }
    return *this;
}

PersonHandle& PersonHandle::changeAttr(string attribute, string value) {
    if(*is_vaild_) {
        // remove self and then update deeply
        remove();
        person_ -> attr(attribute) -> set(value);
        person_ -> update_ID_();

        // after the person's ID is changed, update mb.
        mb_ -> persons_ -> insert(std::pair<string, Person*>(person_ -> ID().raw(), person_));
        mb_ -> order_ -> push_back(person_ -> ID().raw());
        *is_vaild_ = true;

        // save messagebook and reset self
        mb_ -> save();
        reset_();
    } else {
        ; // do nothing
    }
    return *this;
}

// return string if it is vaild (called by function str)
const string PersonHandle::str_() const {
    return "[person handle -> ]\n" + units::add_head(
                person_ -> str_width(76), "...."
            );
}

// return self's json value
shared_ptr<Value> PersonHandle::json_value() {
    throw nojson();
}

string PersonHandle::attr(string attr_) {
    return person_ -> attr(attr_) -> str();
}

void PersonHandle::init() {
    units::Input input(std::cin, std::cout);
    string name, sex, telephone, location, mail_number, email, qq_number, classes;

    input(" | please enter name") >> name;
    input(" | please enter sex [M/F]") >> sex;;
    input(" | please enter telephone [only include digit]") >> telephone;
    input(" | please enter location") >> location;
    input(" | please enter postal number [6-length number]") >> mail_number;
    input(" | please enter email") >> email;
    input(" | please enter qq number") >> qq_number;
    input(" | please enter classes");
    std::cin >> std::ws;
    std::getline(std::cin, classes);
    input(" | ");

    (*this)
        .changeAttr("name", name)
        .changeAttr("sex",  sex)
        .changeAttr("telephone", telephone)
        .changeAttr("location", location)
        .changeAttr("mail_number", mail_number)
        .changeAttr("email", email)
        .changeAttr("qq_number", qq_number)
        .changeAttr("classes", classes)
    ;

    return;
}

}} // for namespace mbc::Val
