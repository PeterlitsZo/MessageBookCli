#ifndef PETERLITS_VAL_H__
#define PETERLITS_VAL_H__

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <list>
#include <map>

#include "../include/rapidjson/document.h"

namespace mbc {

namespace Val {

// ----------------------------------------------------------------------------
// ---[ mbc::Val::Type ]-------------------------------------------------------
// ----------------------------------------------------------------------------

enum Type {
    STR,
    VECSTR,
    PERSON,
    MESSAGEBOOK
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::ValBase ]----------------------------------------------------
// ----------------------------------------------------------------------------

class ValBase {
public:
    virtual ~ValBase();
    ValBase(const ValBase& other);

    const std::string& str() const;
    bool vaild() const;
    const Type& type() const;

    virtual std::shared_ptr<rapidjson::Value> json_value() = 0;

protected:
    virtual const std::string& str_() const = 0;

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
    _ValAtom(const _ValAtom& other);

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
    Str(std::function<bool(const std::string& str)> vaild_checker);
    ~Str();

    const std::string& raw() const;

    std::shared_ptr<rapidjson::Value> json_value();

private:
    const std::string str_() const;

    void init_(const std::string& str);
    void init_();

    std::shared_ptr<std::string> value_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::VecStr ]-----------------------------------------------------
// ----------------------------------------------------------------------------

class VecStr: public _ValAtom {
public:
    VecStr();
    VecStr(std::function<bool(const std::string& str)> vaild_checker);
    ~VecStr();

    std::shared_ptr<rapidjson::Value> json_value();

private:
    const std::string str_() const;

    void init_(const std::string& str);
    void init_();

    typedef std::vector<std::string> vecstr_Type;
    std::shared_ptr<vecstr_Type> value_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::PersonHandle ]-----------------------------------------------
// ----------------------------------------------------------------------------

class MessageBook;
class Person;

class PersonHandle: public ValBase {
public:
    PersonHandle(std::shared_ptr<MessageBook> mb, const std::string& full_id);
    PersonHandle(const PersonHandle& personhandle);
    ~PersonHandle();

    PersonHandle& remove();
    PersonHandle& changeAttr(std::string attribute, std::string value);
    std::shared_ptr<rapidjson::Value> json_value();

private:
    const std::string str_() const;
    void reset_();

    std::shared_ptr<MessageBook>    mb_;
    std::shared_ptr<Person>         person_;
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
    std::string hash_();
    void update_ID_();

    Str ID_;
    Str name_;
    Str sex_;
    Str telephone_;
    Str mail_number_;
    Str email_;
    Str qq_number_;
    Str location_;
    VecStr classes_;
};


// ----------------------------------------------------------------------------
// ---[ mbc::Val::MessageBook ]------------------------------------------------
// ----------------------------------------------------------------------------

class MessageBook: public ValBase {
public:
    MessageBook(const std::string& path);
    ~MessageBook();

    void save();

    PersonHandle newPerson();
    PersonHandle getPerson(std::string brokenID);

    std::shared_ptr<rapidjson::Value> json_value();

    friend class PersonHandle;

private:
    std::string fullID(std::string ID);
    const std::string str_() const;

    std::shared_ptr<std::string> path_;
    std::shared_ptr<std::map<std::string, Person>> persons_;
    std::shared_ptr<std::list<std::string>> order_;

};


} // for namespace Val

} // for namespace mbc

#endif // for ifndef PETERLITS_VAl_H
