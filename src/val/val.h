#ifndef PETERLITS_VAL_H__
#define PETERLITS_VAL_H__

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <exception>

#include "../../include/rapidjson/document.h"

namespace mbc {

namespace Val {

// ----------------------------------------------------------------------------
// ---[ mbc::Val::Exception ]--------------------------------------------------
// ----------------------------------------------------------------------------

struct bad_attr : public std::exception {
    const char* what() throw() {
        return "the attribute is unused";
    }
};


struct bad_value : public std::exception {
    const char* what() throw() {
        return "the value is not standrand";
    }
};


struct too_little : public std::exception {
    const char * what () throw() {
        return "the result's number is too little";
    }
};

// ----------------------------------------------------------------------------
// ---[ mbc::Val::Type ]-------------------------------------------------------
// ----------------------------------------------------------------------------

enum Type {
    BASE,
    ATOM,
    STR,
    VECSTR,
    PERSON,
    PERSONHANDLE,
    MESSAGEBOOK
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::ValBase ]----------------------------------------------------
// ----------------------------------------------------------------------------

class ValBase {
public:
    virtual ~ValBase();
    ValBase();
    ValBase(const ValBase& other);

    const std::string str() const;
    bool vaild() const;
    const Type& type() const;

    operator bool() const;

    virtual std::shared_ptr<rapidjson::Value> json_value() = 0;

protected:
    virtual const std::string str_() const = 0;

    int*                         count_;
    std::string*                 invaild_waring_;
    bool*                        is_vaild_;
    Type*                        type_;

    static                       rapidjson::Document doc_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::_ValAtom ]---------------------------------------------------
// ----------------------------------------------------------------------------

class _ValAtom : public ValBase {
public:
    virtual ~_ValAtom();
    _ValAtom();
    _ValAtom(const _ValAtom& other);
    virtual const std::string& raw() const = 0;

    _ValAtom& set(const std::string& str);
    _ValAtom& operator=(const std::string& str);

protected:
    virtual void init_(const std::string& str) = 0;
    virtual void init_() = 0;

    std::function<bool(const std::string& str)>* vaild_checker_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::Str ]--------------------------------------------------------
// ----------------------------------------------------------------------------

class Str: public _ValAtom {
public:
    Str();
    Str(const Str& other);
    Str(std::function<bool(const std::string& str)> vaild_checker);
    ~Str();

    _ValAtom& reprset(const std::string& str);

    const std::string& raw() const;

    std::shared_ptr<rapidjson::Value> json_value();

    bool operator < (const Str& other);

private:
    const std::string str_() const;

    void init_(const std::string& str);
    void init_();

    std::string* value_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::VecStr ]-----------------------------------------------------
// ----------------------------------------------------------------------------

class VecStr: public _ValAtom {
public:
    VecStr();
    VecStr(const VecStr& other);
    VecStr(std::function<bool(const std::string& str)> vaild_checker);
    ~VecStr();

    const std::string& raw() const; 

    std::shared_ptr<rapidjson::Value> json_value();

private:
    const std::string str_() const;

    void init_(const std::string& str);
    void init_();

    std::vector<std::string>* value_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::PersonHandle ]-----------------------------------------------
// ----------------------------------------------------------------------------

class MessageBook;
class Person;

class PersonHandle: public ValBase {
public:
    PersonHandle(MessageBook* mb, Person* person);
    PersonHandle(const PersonHandle& other);
    ~PersonHandle();

    PersonHandle& remove();
    std::string attr(std::string attr);
    PersonHandle& changeAttr(std::string attribute, std::string value);
    std::shared_ptr<rapidjson::Value> json_value();

    void init();

private:
    const std::string str_() const;
    void reset_();

    MessageBook*                    mb_;
    Person*                         person_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::Person ]-----------------------------------------------------
// ----------------------------------------------------------------------------

class Person: public ValBase {
public:
    Person();
    Person(const Person& person);
    ~Person();

    const Str& ID() const;
    _ValAtom* attr(std::string attribute);

    std::shared_ptr<rapidjson::Value> json_value();

    friend class PersonHandle;

private:
    const std::string str_() const;
    const std::string str_width(int width) const;
    std::string hash_();
    void update_ID_();

    Str* ID_;
    Str* name_;
    Str* sex_;
    Str* telephone_;
    Str* mail_number_;
    Str* email_;
    Str* qq_number_;
    Str* location_;
    VecStr* classes_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::MessageBook ]------------------------------------------------
// ----------------------------------------------------------------------------

class MessageBook: public ValBase {
public:
    MessageBook(const std::string& path);
    MessageBook(const MessageBook& other);
    ~MessageBook();

    void save();
    void sort(std::string attr);
    PersonHandle sreach(std::string attr, std::string thing);

    PersonHandle newPerson();
    PersonHandle getPerson(std::string brokenID);

    std::shared_ptr<rapidjson::Value> json_value();

    friend class PersonHandle;

private:
    Str fullID(Str ID);
    const std::string str_() const;

    Str*                             path_;
    std::map<std::string, Person*>*  persons_;
    std::list<std::string>*          order_;

};


} // for namespace Val

} // for namespace mbc

#endif // for ifndef PETERLITS_VAl_H
