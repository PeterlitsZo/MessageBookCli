#include "val.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <functional>
#include <memory>
#include <type_traits>
#include <exception>

#include "../../include/rapidjson/writer.h"
#include "../../include/rapidjson/document.h"
#include "../../include/rapidjson/stringbuffer.h"

#include "../units.h"

using std::string;
using std::function;
using std::shared_ptr;
using std::make_shared;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::list;
using std::map;

using rapidjson::Value;
using rapidjson::Document;
using rapidjson::StringBuffer;
using rapidjson::Writer;

namespace mbc { namespace Val { // begin for namespace mbc::Val

struct bad_ID : public std::exception {
    const char* what() throw() {
        return "the broken ID has not its full ID";
    }
};


MessageBook::MessageBook(const MessageBook& other) : ValBase(other) {
    path_ = other.path_;
    persons_ = other.persons_;
    order_ = other.order_;
}

MessageBook::MessageBook(const string& path) : ValBase() {
    using units::repr;

    path_ = new Str();
    path_ -> set(path);
    order_ = new list<string>();
    persons_ = new map<string, Person*>();

    *invaild_waring_ = "[ invaild message book ]";
    *is_vaild_ = true;

    ifstream in(path);
    if(!in) {
        // empty persons_ map and empty order_ list
        return;
    }
    stringstream buffer;
    buffer << in.rdbuf();
    string content(buffer.str());

    doc_.Parse(content.c_str());

    for(auto it = doc_.Begin(); it != doc_.End(); ++it) {
        vector<string> result;
        auto value = (*it)["classes"]["value"].GetArray();
        for(auto itor = value.Begin(); itor != value.End(); ++itor) {
            result.push_back(itor -> GetString());
        }

        newPerson()
            .changeAttr("name",        (*it)["name"]["value"].GetString())
            .changeAttr("sex",         (*it)["sex"]["value"].GetString())
            .changeAttr("telephone",   (*it)["telephone"]["value"].GetString())
            .changeAttr("location",    (*it)["location"]["value"].GetString())
            .changeAttr("mail_number", (*it)["mail_number"]["value"].GetString())
            .changeAttr("email",       (*it)["email"]["value"].GetString())
            .changeAttr("qq_number",   (*it)["qq_number"]["value"].GetString())
            .changeAttr("classes",     repr(result.begin(), result.end()))
        ;
    }
}

MessageBook::~MessageBook() {
    if(*count_ == 1) {
        delete path_;
        delete persons_;
        delete order_;
    }
}

const string MessageBook::str_() const {
    string result;
    for(auto it = order_ -> cbegin(); it != order_ -> cend(); ++ it) {
        result += persons_ -> find(*it) -> second -> str();
        result += "\n\n";
    }
    return result;
}

Str MessageBook::fullID(Str ID) {
    for(auto it = order_ -> begin(); it != order_ -> end(); ++it) {
        if (units::start_with(*it, ID.raw())) {
            Str result;
            result.set(*it);
            return result;
        }
    }
    throw bad_ID();
}

shared_ptr<Value> MessageBook::json_value() {
    shared_ptr<Value> value = make_shared<Value>();
    value -> SetArray();
    auto& allo = doc_.GetAllocator();

    for(auto it = persons_ -> begin(); it != persons_ -> end(); ++it) {
        value -> PushBack(*(it -> second -> json_value()), allo);
    }
    return value;
}

void MessageBook::save() {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json_value() -> Accept(writer);

    ofstream out(path_ -> raw());
    out << buffer.GetString();
}

PersonHandle MessageBook::newPerson() {
    Person* person = new Person();
    if (not persons_ -> count(person -> ID().raw())) {
        order_ -> push_back(person -> ID().raw());
        persons_ -> insert({person -> ID().raw(), person});
        save();
    }
    return PersonHandle(this,
                        (*persons_)[person -> ID().raw()] );
    // [WARNING] I don't delete it!!!
}

PersonHandle MessageBook::getPerson(string brokenID) {
    auto str = Str();
    str.set(brokenID);
    return PersonHandle(this,
                        (*persons_)[fullID(str).raw()]);
}

PersonHandle MessageBook::sreach(string thing, string attr_) {
    auto it = std::find_if(persons_ -> begin(), persons_ -> end(),
            [&](const std::pair<string, Person*>& pair) {
                return pair.second -> attr(attr_) -> raw() == thing;
            });
    if(it != persons_ -> end()) {
        return PersonHandle(this, it -> second);
    } else {
        return newPerson();
        // throw "the result of sreach is too little";
    }
}

void MessageBook::sort(string attr_) {
    order_ -> sort([&](const string& a, const string& b) {
        return getPerson(a).attr(attr_) < getPerson(b).attr(attr_);
    });
}

}} // for namespace mbc::Val


