#ifndef PETERLITS_VALUE_H__
#define PETERLITS_VALUE_H__

#include <iostream>
#include <string>
#include <type_traits>

#include "../include/rapidjson/document.h"

using std::string;

template<typename T>
class Value {
public:
    Value(T value): is_valid_(true), value_(value){};
    Value(): is_valid_(false), value_(T()){};
    void operator=(T value) {value_ = value; is_valid_ = true;}

    rapidjson::Value* get_rapidjson_value(rapidjson::Document::AllocatorType& allo_ptr);

    template<typename S>
    friend std::ostream& operator<<(std::ostream& out, const Value<S>& it);

private:
    bool is_valid_;
    T    value_;
};

template<>
class Value<string> {
public:
    Value(string value): is_valid_(true), value_(value){};
    Value(): is_valid_(false), value_(""){};
    void operator=(string value) {value_ = value; is_valid_ = true;}

    rapidjson::Value* get_rapidjson_value(rapidjson::Document::AllocatorType& allo) {
        rapidjson::Value* v = new rapidjson::Value();
        v->SetObject();
        
        v->AddMember("valid", is_valid_, allo);
        v->AddMember("value",
                     rapidjson::Value(value_.c_str(), allo).Move(),
                     allo);
        return v;
    }

    template<typename S>
    friend std::ostream& operator<<(std::ostream& out, const Value<S>& it);

private:
    bool      is_valid_;
    string    value_;
};

// ----------------------------------------------------------------------------
// ---[ units part ]-----------------------------------------------------------
// ----------------------------------------------------------------------------

template <typename S>
std::ostream& operator<<(std::ostream& out, const Value<S>& it) {
    if (it.is_valid_) {
        out << it.value_;
    } else {
        out << "[invaild]";
    }
    return out;
}

// [WARNING]: remember to delete it! (should I?)
template <typename T>
rapidjson::Value* Value<T>::get_rapidjson_value(
        rapidjson::Document::AllocatorType& allo) {
    rapidjson::Value* v = new rapidjson::Value();
    v->SetObject();
    
    v->AddMember("valid", is_valid_, allo);
    v->AddMember("value", value_, allo);
    return v;
}

#endif // for PETERLITS_VALUE_H__

