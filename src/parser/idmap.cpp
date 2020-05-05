#include "idmap.h"

#include <clocale>
#include <map>
#include <memory>

#include "../val/val.h"
#include <pthread.h>

using std::string;
using std::shared_ptr;


shared_ptr<mbc::Val::ValBase> Idmap::get (string name) {
    if (idmap_.count(name)) {
        return idmap_[name];
    } else {
        throw "Error! the idmap do not have the variable";
    }
}


void Idmap::update(string name, shared_ptr<mbc::Val::ValBase> ptr) {
    idmap_[name] = ptr;
}
