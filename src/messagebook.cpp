#include "messagebook.h"

#include <alloca.h>
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>

// for read and write json file
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/stringbuffer.h"

#include "person.h"
#include "units.h"
#include "person_ptr.h"
#include "value.h"

using std::string;
using std::istream;
using std::ostream;
using std::vector;
using std::list;

using rapidjson::Document;

// ----------------------------------------------------------------------------
// ---[ units function ]-------------------------------------------------------
// ----------------------------------------------------------------------------
const char* getString(rapidjson::Value& value) {
    if(value["valid"].GetBool()) {
        return value["value"].GetString();
    } else {
        return "";
    }
}

vector<string> getVecString(rapidjson::Value& value) {
    vector<string> result;
    for(auto it = value.Begin(); it != value.End(); ++it) {
        result.push_back(it->GetString());
    }
    return result;
}

// ----------------------------------------------------------------------------
// ---[ method part ]----------------------------------------------------------
// ----------------------------------------------------------------------------

// ---[ inital method ]--------------------------------------------------------

// inital by the path of json file
MessageBook::MessageBook(const char* path) {
    path_ = path;
    // read all file into string
    std::ifstream in(path);
    // open failed!
    if(!in) {
        return;
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content(buffer.str());

    // parser the json c-string
    rapidjson::Document doc;
    doc.Parse(content.c_str());

    for(auto it = doc.MemberBegin(); it != doc.MemberEnd(); ++it) {
        addPerson(getString(it->value["name"]),
                  getString(it->value["sex"]),
                  getString(it->value["telephone"]),
                  getString(it->value["location"]),
                  getString(it->value["mail_number"]),
                  getString(it->value["email"]),
                  getString(it->value["qq_number"]),
                  getVecString(it->value["classes"]));
    }
}

// ---[ units method ]---------------------------------------------------------

// addPerson

void MessageBook::addPerson(string name, string sex, string telephone, string location, 
                            string mail_number, string email, string qq_number, 
                            vector<string> classes) {
    Person person(name, sex, telephone, location, mail_number, email, qq_number, classes);
    // person.setID(person.hash());
    persons_[person.hash()] = person;
    order_.push_back(person.ID());
}

void MessageBook::addPerson(istream& in, ostream& out) {
    Person person(in, out);
    // person.setID(person.hash());
    persons_[person.hash()] = person;
    order_.push_back(person.ID());
}

void MessageBook::addPerson(Person p) {
    persons_[p.ID()] = p;
    order_.push_back(p.ID());
}

PersonPtr* MessageBook::addPerson(void) {
    Person person;
    persons_[person.hash()] = person;
    order_.push_back(person.ID());
    return new PersonPtr(*this, person.hash());
}

// save

void MessageBook::save() {
    using rapidjson::StringBuffer;
    using rapidjson::Writer;
    using rapidjson::Value;

    // d -> Null Array
    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.SetObject();

    for (auto it = persons_.begin(); it != persons_.end(); ++it) {
        rapidjson::Value* value = it->second.get_rapidjson_value(allocator);
        d.AddMember(Value(it->first.c_str(), allocator).Move(), *value, allocator);
        delete value;
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    std::ofstream out(path_.c_str());
    out << buffer.GetString();
}

// remove

void MessageBook::remove(string ID) {
    persons_.erase(ID);
    auto ID_iter = std::find(order_.begin(), order_.end(), ID);
    order_.erase(ID_iter);
}

// sreach

string MessageBook::sreach(string at, string thing) {
    auto it = std::find_if(persons_.begin(), persons_.end(),
        [&](const std::pair<string, Person>& pair) {
            // return true;
            return pair.second.attr(at) == thing;
        });
    return it->second.str();
}

// get_raw

Person& MessageBook::get_raw(string ID) {
    return persons_[ID];
}

// get

PersonPtr MessageBook::get(std::string ID) {
    // what will happen if cannot find anything? -> a ID = "" personptr!
    return PersonPtr(*this, getfullID(ID));
}

// str

string MessageBook::str() const {
    if (persons_.size() == 0 ) {
        return "[ empty list ]";
    }
    string result;
    for (auto it = order_.begin(); it != order_.end(); ++it) {
        result += persons_.find(*it)->second.str();
        result += '\n';
    }
    return result;
}

// operator<<

std::ostream& operator<<(std::ostream& out, const MessageBook& mb) {
    out << mb.str();
    return out;
}

// getfullID

string MessageBook::getfullID(string ID) {
    for(auto it = persons_.begin(); it != persons_.end(); ++it) {
        if( units::start_with(it->first, ID) ) {
            return it->first;
        }
    }
    return "";
}

// sort

void MessageBook::sort(string at) {
    order_.sort([&](const string& a, const string& b) {
        return get_raw(a).attr(at) < get_raw(b).attr(at);
    });
}

