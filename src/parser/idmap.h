#ifndef PETERLITS_IDMAP_H__
#define PETERLITS_IDMAP_H__

#include <cstdint>
#include <map>
#include <string>

#include "../person_ptr.h"

struct IdmapValue {
    enum TYPE {
        PERSON,
        STRING,
    } type;
    union VALUE {
        PersonPtr*     p;
        std::string*   s;
    } value;
    std::string str();
};

class Idmap {
public:
    Idmap();

    IdmapValue& operator[] (std::string);

private:
    std::map<std::string, IdmapValue> idmap_;
};

#endif // for PETERLITS_IDMAP_H__
