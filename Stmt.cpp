#include "Expr.h"
#include "Stmt.h"

using namespace std;

namespace {

  void spaces(ostream& os, int n) {
    for (int i = 0; i < n; i++)
      os << "  ";
  }

}

void BlockStmt::print(ostream& os, int indent) {
  os << "{" << endl;
  list<Stmt*>::iterator iter = _stmts->begin();
  bool more = iter != _stmts->end();
  while (more) {
    spaces(os, indent+1);
    (*iter)->print(os, indent+1);
    ++iter;    
    more = iter != _stmts->end();
    os << endl;
  }
  spaces(os, indent);
  os << "}";
}

void Var::print(ostream& os, int indent) {
  cout << _name;
  if (_expr) {
    os << " = ";
    _expr->print(os, indent);
  }
}

void DeclStmt::print(ostream& os, int indent) {
  os << "var ";
  list<Var*>::iterator iter = _vars->begin();
  bool more = iter != _vars->end();
  while (more) {
    (*iter)->print(os, indent+1);
    ++iter;
    more = iter != _vars->end();
    if (more)
      os << ", ";
  }
  os << ";";
}

void IfStmt::print(ostream& os, int indent) {
  os << "if (";
  _cond->print(os, indent);
  os << ")" << endl;
  spaces(os, indent+1);
  _yesStmt->print(os, indent);
  if (_noStmt) {
    os << " else" << endl;
    spaces(os, indent+1);
    _noStmt->print(os, indent+1);
  }
}

void WhileStmt::print(ostream& os, int indent) {
  os << "while (";
  _cond->print(os, indent);
  os << ") ";
  _body->print(os, indent);
}

void ReturnStmt::print(ostream& os, int indent) {
  os << "return ";
  if (_expr) _expr->print(os, indent+1);
  os << ";";
}
