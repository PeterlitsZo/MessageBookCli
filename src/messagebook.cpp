#include "messagebook.h"

#include <alloca.h>
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

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
void MessageBook::addPerson(string name, string sex, string telephone, string location, 
                            string mail_number, string email, string qq_number, 
                            Classes classes) {
    Person person(name, sex, telephone, location, mail_number, email, qq_number, classes);
    person.setID(person.hash());
    persons[person.hash()] = person;
}

void MessageBook::addPerson(istream& in, ostream& out) {
    Person person(in, out);
    person.setID(person.hash());
    persons[person.hash()] = person;
}

void MessageBook::addPerson(Person p) {
    persons[p.ID()] = p;
}

string MessageBook::addPerson(void) {
    Person person;
    persons[person.hash()] = person;
    return person.hash();
}

void MessageBook::save() {
    using rapidjson::StringBuffer;
    using rapidjson::Writer;
    using rapidjson::Value;

    // d -> Null Array
    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.SetObject();

    for (auto it = persons.begin(); it != persons.end(); ++it) {
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

void MessageBook::remove(string ID) {
    persons.erase(ID);
}

Person& MessageBook::get_raw(string ID) {
    return persons[ID];
}

PersonPtr MessageBook::get(std::string ID) {
    return PersonPtr(*this, getfullID(ID));
}

std::ostream& operator<<(std::ostream& out, const MessageBook& mb) {
    for (auto it = mb.persons.begin(); it != mb.persons.end(); ++it) {
        out << it->second;
        out << '\n';
    }
    return out;
}

string MessageBook::getfullID(string ID) {
    for(auto it = persons.begin(); it != persons.end(); ++it) {
        if( units::start_with(it->first, ID) ) {
            return it->first;
        }
    }
    return "";
}

