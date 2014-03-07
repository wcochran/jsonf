#include <list>
#include <vector>
#include <map>
#include "Expr.h"
#include "Stmt.h"

using namespace std;

namespace {

  void spaces(ostream& os, int n) {
    for (int i = 0; i < n; i++)
      os << "  ";
  }

}

void ObjectExpr::print(ostream& os, int indent) {
  os << "{" << endl; 
  std::list<Member*>::iterator iter = _members->begin();
  bool more = iter != _members->end();
  while (more) {
    spaces(os, indent+1);
    (*iter)->print(os, indent+1);
    ++iter;    
    more = iter != _members->end();
    if (more)
      os << ",";
    os << endl;
  }
  spaces(os, indent);
  os << "}";
}

void ArrayExpr::print(ostream& os, int indent) {
  os << "[" << endl;
  std::list<Expr*>::iterator iter = _elems->begin();
  bool more = iter != _elems->end();
  while (more) {
    spaces(os, indent + 1);
    (*iter)->print(os, indent+1);
    ++iter;    
    more = iter != _elems->end();
    if (more)
      os << ",";
    os << endl;
  }
  spaces(os, indent);
  os << "]";
}


void FuncExpr::print(ostream& os, int indent) {
  os << "func (";
  list<string>::iterator iter = _params->begin();
  while (iter != _params->end()) {
    os << *iter;
    ++iter;
    if (iter != _params->end())
      os << ", ";
  }
  os << ") ";
  _body->print(os, indent+1);
}

void AssignExpr::print(ostream& os, int indent) {
  _lval->print(os, indent);
  os << " = ";
  _rval->print(os, indent);
}

namespace {

  void printOp(ostream& os, ExprOp op) {
    switch(op) {
    case OR_OP:   os << " || "; break;
    case AND_OP:  os << " && "; break;
    case EQ_OP:   os << " == "; break;
    case NE_OP:   os << " |= "; break;
    case LT_OP:   os << " < "; break;
    case LE_OP:   os << " <= "; break;
    case GT_OP:   os << " > "; break;
    case GE_OP:   os << " >= "; break;
    case ADD_OP:  os << " + "; break;
    case SUB_OP:  os << " - "; break;
    case MUL_OP:  os << " * "; break;
    case DIV_OP:  os << " / "; break;
    case MOD_OP:  os << " % "; break;
    case NOT_OP:  os << " ! "; break;
    case NEG_OP:  os << " - "; break;
    }
  }

}
 
void BinaryExpr::print(ostream& os, int indent) {
  _left->print(os,indent);
  printOp(os, _op);
  _right->print(os, indent);
}

void UnaryExpr::print(ostream& os, int indent) {
  printOp(os, _op);
  _expr->print(os, indent);
}

void MemberRefExpr::print(ostream& os, int indent) {
  _object->print(os, indent);
  os << " . " << _field;
}

void ArrayRefExpr::print(ostream& os, int indent) {
  _array->print(os, indent);
  os << " [ ";
  _index->print(os, indent);
  os << " ] ";
}

void CallExpr::print(ostream& os, int indent) {
  _func->print(os, indent);
  os << " (";
  std::list<Expr*>::iterator iter = _args->begin();
  bool more = iter != _args->end();
  while (more) {
    (*iter)->print(os, indent+1);
    ++iter;
    more = iter != _args->end();
    if (more)
      os << ",";
  }
  os << ")";
}

