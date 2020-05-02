#include "val.h"

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

#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/logging/easylogging++.h"

#include "units.h"

using std::string;
using std::function;
using std::shared_ptr;
using std::make_shared;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;

using rapidjson::Value;
using rapidjson::Document;
using rapidjson::StringBuffer;
using rapidjson::Writer;

namespace mbc { namespace Val { // begin for namespace mbc::Val

struct bad_ID : public std::exception {
    const char* what() const throw() {
        return "the broken ID has not its full ID";
    }
};

MessageBook::MessageBook(const string& path) {
    using units::repr;

    path_ = make_shared<std::string>(path);
    invaild_waring_ = make_shared<string>("[ invaild message book ]");
    is_vaild_ = true;

    order_ = make_shared<std::list<string>>();
    persons_ = make_shared<std::map<string, Person>>();

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
        auto classes_vecstr = [&]() {
            // function to return it["classes"]'s string value
            vector<string> result;
            auto value = (*it)["classes"]["value"].GetArray();
            for(auto itor = value.Begin(); itor != value.End(); ++itor) {
                result.push_back(itor -> GetString());
            }
            return result;
        } ();

        newPerson()
            .changeAttr("name", repr((*it)["name"]["value"].GetString()))
            .changeAttr("sex", repr((*it)["sex"]["value"].GetString()))
            .changeAttr("telephone", repr((*it)["telephone"]["value"].GetString()))
            .changeAttr("location", repr((*it)["location"]["value"].GetString()))
            .changeAttr("mail_number", repr((*it)["mail_number"]["value"].GetString()))
            .changeAttr("email", repr((*it)["email"]["value"].GetString()))
            .changeAttr("qq_number", repr((*it)["qq_number"]["value"].GetString()))
            .changeAttr("classes", repr(classes_vecstr.begin(), classes_vecstr.end()))
        ;
    }
}

MessageBook::~MessageBook() {
    ; // do nothing;
}

const string MessageBook::str_() const {
    string result;
    for(auto it = order_ -> cbegin(); it != order_ -> cend(); ++ it) {
        result += persons_ -> find(*it) -> second.str();
        result += "\n\n";
    }
    return result;
}

string MessageBook::fullID(string ID) {
    for(auto it = order_ -> begin(); it != order_ -> end(); ++it) {
        if (units::start_with(*it, ID)) {
            return *it;
        }
    }
    throw bad_ID();
}

shared_ptr<Value> MessageBook::json_value() {
    shared_ptr<Value> value = make_shared<Value>();
    value -> SetArray();
    auto& allo = doc_.GetAllocator();

    for(auto it = persons_ -> begin(); it != persons_ -> end(); ++it) {
        value -> PushBack(*(it -> second.json_value()), allo);
    }
    return value;
}

void MessageBook::save() {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json_value() -> Accept(writer);

    ofstream out(path_ -> c_str());
    out << buffer.GetString();
}

PersonHandle MessageBook::newPerson() {
    Person person;
    if (not persons_ -> count(person.ID().raw())) {
        order_ -> push_back(person.ID().raw());
    }
    (*persons_)[person.ID().raw()] = person;
    save();
    return PersonHandle(std::make_shared<MessageBook>(*this),
                        person.ID().raw());
}

PersonHandle MessageBook::getPerson(string brokenID) {
    return PersonHandle(std::make_shared<MessageBook>(*this),
                        fullID(brokenID));
}

}} // for namespace mbc::Val
