#ifndef PETERLITS_IDMAP_H__
#define PETERLITS_IDMAP_H__

#include <cstdint>
#include <map>
#include <string>

#include "../person_ptr.h"

// struct IdmapValue {
//     enum TYPE {
//         PERSON,
//         STRING,
//     } type;
//     union VALUE {
//         PersonPtr*     p;
//         std::string*   s;
//     } value;
//     std::string str();
// };

enum Val_T {
    PER,    // person
    STR,    // string
    NUL,    // null
};

class Val {
public:
    Val(PersonPtr* ptr);
    Val(std::string* ptr);
    Val();

    std::string str();

    PersonPtr* getPersonPtr();
    std::string* getString();
    void del();
private:
    Val_T type_;
    union V {
        PersonPtr*   p;
        std::string* s;
    } val_;
};

class Idmap {
public:
    Idmap();
     ~Idmap();

//     // Val& operator[] (std::string);
    void update(std::string name, Val* value);
    Val* get(std::string name);

private:
    std::map<std::string, Val*> idmap_;
};

#endif // for PETERLITS_IDMAP_H__
