#include "messagebook.h"

#include <ostream>
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

void MessageBook::addPerson(string name, string sex, string telephone, string location, 
                            string mail_number, string email, string qq_number, 
                            Classes classes) {
    Person person(name, sex, telephone, location, mail_number, email, qq_number, classes);
    person.setID(++lastID_);
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
