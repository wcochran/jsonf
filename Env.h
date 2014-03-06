#ifndef ENV_H
#define ENV_H

#include "Value.h"
#include <map>
#include <string>

class Env {
  std::map<std::string,Value*> _tbl;
  Env *_prev;
public:
  Env(Env *prev) : _tbl(), _prev(prev) {}
  Value *get(const std::string& name);
  void put(const std::string& name, Value *val) {
    _tbl[name] = val;
  }
};

#endif // ENV_H
