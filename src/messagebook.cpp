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

// units function
const char* getString(rapidjson::Value& value) {
    if(value["valid"].GetBool()) {
        return value["value"].GetString();
    } else {
        return "";
    }
}

// inital by the path of json file
MessageBook::MessageBook(const char* path):lastID_(0) {
    // read all file into string
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content(buffer.str());

    // parser the json c-string
    rapidjson::Document document;
    document.Parse(content.c_str());

    for(auto& person: document.GetArray()) {
        addPerson(getString(person["name"]),
                  getString(person["sex"]),
                  getString(person["telephone"]),
                  getString(person["location"]),
                  getString(person["mail_number"]),
                  getString(person["email"]),
                  getString(person["qq_number"]),
                  {});
    }
}

// units method
void MessageBook::addPerson(string name, string sex, string telephone, string location, 
                            string mail_number, string email, string qq_number, 
                            Classes classes) {
    Person person(name, sex, telephone, location, mail_number, email, qq_number, classes);
    person.setID(person.hash());
    persons.push_back(person);
}

void MessageBook::save(const char* path) {
    using rapidjson::StringBuffer;
    using rapidjson::Writer;
    // d -> Null Array
    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.SetArray();

    // v -> Null Array
    // rapidjson::Value v(rapidjson::kArrayType);

    for (auto &person: persons) {
        rapidjson::Value* value = person.get_rapidjson_value(allocator);
        d.PushBack(*value, allocator);
        delete value;
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    std::ofstream out(path);
    out << buffer.GetString();
}

std::ostream& operator<<(std::ostream& out, const MessageBook& mb) {
    for(auto person: mb.persons) {
        out << person;
        out << '\n';
    }
    return out;
}
