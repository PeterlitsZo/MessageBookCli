#ifndef PETERLITS_VALUE_H__
#define PETERLITS_VALUE_H__

#include <iostream>

template<typename T>
class Value {
public:
    Value(T value): is_valid_(true), value_(value){};
    Value(): is_valid_(false), value_(T()){};
    void operator=(T value) {value_ = value; is_valid_ = true;}

    template<typename S>
    friend std::ostream& operator<<(std::ostream& out, const Value<S>& it);

private:
    bool is_valid_;
    T    value_;
};

template<typename S>
std::ostream& operator<<(std::ostream& out, const Value<S>& it) {
    if (it.is_valid_) {
        out << it.value_;
    } else {
        out << "[invaild value]";
    }
    return out;
}


#endif // for PETERLITS_VALUE_H__
