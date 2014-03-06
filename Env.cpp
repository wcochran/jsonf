#include "Env.h"

using namespace std;

Value *Env::get(const std::string& name) {
  Env *env = this;
  do {
    map<string,Value*>::iterator iter = env->_tbl.find(name);
    if (iter != _tbl.end())
      return iter->second;
    env = env->_prev;
  } while (env);
  return 0;
}
