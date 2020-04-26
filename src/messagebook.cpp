#include "messagebook.h"

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

using std::string;
using std::istream;
using std::ostream;
using std::vector;

// units function
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
                  // {});
                  getVecString(it->value["classes"]));
    }
}

// units method
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

void MessageBook::save() {
    using rapidjson::StringBuffer;
    using rapidjson::Writer;
    using rapidjson::Value;

    // d -> Null Array
    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.SetObject();

    for (auto &&[key, person]: persons) {
        rapidjson::Value* value = person.get_rapidjson_value(allocator);
        d.AddMember(Value(key.c_str(), allocator).Move(), *value, allocator);
        delete value;
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    std::ofstream out(path_.c_str());
    out << buffer.GetString();
}

std::ostream& operator<<(std::ostream& out, const MessageBook& mb) {
    for(auto &&[key, person]: mb.persons) {
        out << person;
        out << '\n';
    }
    return out;
}

