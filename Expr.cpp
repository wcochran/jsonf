#include <list>
#include <vector>
#include <map>
#include "Expr.h"

using namespace std;

namespace {

  ostream& spaces(ostream& os, int n) {
    for (int i = 0; i < n; i++)
      os << "  ";
    return os;
  }

}

ostream& Member::print(ostream& os, int indent) {
  os << _name << " : ";
  _expr->print(os, indent);
  return os;
} 

ostream& ObjectExpr::print(ostream& os, int indent) {
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
  return os << "}";
}

ostream& ArrayExpr::print(ostream& os, int indent) {
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
  return os << "]";
}

ostream& StringExpr::print(ostream& os, int indent) {
  return os << _str;
}

ostream& NumExpr::print(ostream& os, int indent) {
  return os << _num;
}

ostream& BoolExpr::print(ostream& os, int indent) {
  return os << (_bool ? "true" : "false");
}

ostream& NullExpr::print(ostream& os, int indent) {
  return os << "null";
}

ostream& FuncExpr::print(ostream& os, int indent) {
  return os << "\"<Func>\"";
}

ostream& AssignExpr::print(ostream& os, int indent) {
  return os << _lval->print(os, indent) << " = " << _rval->print(os, indent);
}

namespace {

  ostream& printOp(ostream& os, ExprOp op) {
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
    return os;
  }

}
 

ostream& BinaryExpr::print(ostream& os, int indent) {
  return os << _left->print(os,indent) << printOp(os, _op) 
	    << _right->print(os, indent);
}

ostream& UnaryExpr::print(ostream& os, int indent) {
  return os << printOp(os, _op) << _expr->print(os, indent);
}

ostream& MemberRefExpr::print(ostream& os, int indent) {
  return os << _object->print(os, indent) << " . " << _field;
}

ostream& ArrayRefExpr::print(ostream& os, int indent) {
  return os << _array->print(os, indent) << " [ " 
	    << _index->print(os, indent) << " ] ";
}

ostream& CallExpr::print(ostream& os, int indent) {
  return os << _func->print(os, indent) << " ( " << endl;
  std::list<Expr*>::iterator iter = _args->begin();
  bool more = iter != _args->end();
  while (more) {
    spaces(os, indent + 1);
    os << (*iter)->print(os, indent+1);
    ++iter;
    more = iter != _args->end();
    if (more)
      os << ",";
    os << endl;
  }
  return os << ")";
}

