#ifndef PETERLITS_IDMAP_H__
#define PETERLITS_IDMAP_H__

#include <map>
#include <string>
#include <memory>

#include "../val.h"

class Idmap {
public:
    std::shared_ptr<mbc::Val::ValBase> get(std::string name);
    void update(std::string name, std::shared_ptr<mbc::Val::ValBase> ptr);

private:
    std::map<std::string, std::shared_ptr<mbc::Val::ValBase>> idmap_;
};

#endif
