#include <list>
#include <vector>
#include <map>
#include "Expr.h"

using namespace std;

Value *ObjectExpr::eval(Env *env) {
  list<pair<string,Value*> > members;
  // XXXX
}
