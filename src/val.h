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
    VecStr(rapidjson::Document::AllocatorType& allocator);

    std::string str();
    rapidjson::Value* get_json_value();

private:
    std::vector<std::string>* value_;
};

} // for namespace Val

} // for namespace mbc

#endif // for PETERLITS_VAL_H___
