#ifndef PETERLITS_VAL_H___
#define PETERLITS_VAL_H___

#include <string>
#include <vector>

#include "../include/rapidjson/document.h"

namespace mbc {

// ----------------------------------------------------------------------------
// ---[ Base ]-----------------------------------------------------------------
// ----------------------------------------------------------------------------

class ValBase {
public:
    ValBase(rapidjson::Document::AllocatorType& allocator);

    virtual std::string str() = 0;
    virtual rapidjson::Value* get_json_value() = 0;
protected:
    bool is_vaild_;
    rapidjson::Document::AllocatorType& json_allocator_;
};


// ----------------------------------------------------------------------------
// ---[ Child ]----------------------------------------------------------------
// ----------------------------------------------------------------------------

namespace Val {

// ---[ Val::Str ]-------------------------------------------------------------

class Str : public ValBase {
public:
    Str(rapidjson::Document::AllocatorType& allocator,
        std::string string);
    Str(rapidjson::Document::AllocatorType& allocator);
    void set(const Str& str);

    std::string str();
    rapidjson::Value* get_json_value();

private:
    std::string* value_;
};

// ---[ Val::VecStr ]----------------------------------------------------------

class VecStr : public ValBase {
public:
    VecStr(rapidjson::Document::AllocatorType& allocator,
           std::vector<std::string> vecstr);
    VecStr(rapidjson::Document::AllocatorType& allocator,
           std::string str);
    VecStr(rapidjson::Document::AllocatorType& allocator);
    void set(const VecStr& vecstr);

    std::string str();
    rapidjson::Value* get_json_value();

private:
    std::vector<std::string>* value_;
};

// ---[ Val::Person ]----------------------------------------------------------

class Person : public ValBase {
public:
    Person(rapidjson::Document::AllocatorType& allocator);
    Person(rapidjson::Document::AllocatorType& allocator,
           std::string name, std::string sex, std::string telephone,
           std::string location, std::string mail_number, std::string email,
           std::string qq_number, std::string classes);
    void set(const Person& person);

    std::string ID();

    std::string str();
    rapidjson::Value* get_json_value();

private:
    void init(std::string name, std::string sex, std::string telephone,
              std::string location, std::string mail_number, std::string email,
              std::string qq_number, std::string classes);
    void init();
    std::string hash();

    Str ID_;
    Str name_;
    Str sex_;
    Str telephone_;
    Str location_;
    Str mail_number_;
    Str email_;
    Str qq_number_;
    VecStr classes_;
};

} // for namespace Val

} // for namespace mbc

#endif // for PETERLITS_VAL_H___
