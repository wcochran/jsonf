#ifndef EXPR_H
#define EXPR_H

#include <list>
#include <vector>
#include <map>
#include "Value.h"
#include "Env.h"

struct Stmt;

extern int yylineno;

class Expr {
public:
  const int _lineno;
  Expr() : _lineno(yylineno) {}
  virtual ~Expr() {}
  virtual Value *eval(Env *env) {return 0;} // XXX
  virtual void print(std::ostream& os, int indent) = 0;  
};

struct Member {
  const int _lineno;
  const std::string _name;
  Expr *_expr;
  Member(const std::string& n, Expr *e) 
    : _lineno(yylineno), _name(n), _expr(e) {}
  virtual void print(std::ostream& os, int indent);  
};

class ObjectExpr : public Expr {
  std::list<Member*> *_members;
public:
  ObjectExpr(std::list<Member*> *members = 0) : _members(members) {}
  virtual void print(std::ostream& os, int indent);  
};

class ArrayExpr : public Expr {
  std::list<Expr*> *_elems;
public:
  ArrayExpr(std::list<Expr*> *elems = 0) : _elems(elems) {}
  virtual void print(std::ostream& os, int indent);  
};

class StringExpr : public Expr {
public:
  const std::string _str;
  StringExpr(const std::string& s) : _str(s) {}
  virtual void print(std::ostream& os, int indent);  
};

class NumExpr : public Expr {
public:
  const double _num;
  NumExpr(double n) : _num(n) {}
  virtual void print(std::ostream& os, int indent);  
};

class BoolExpr : public Expr {
public:
  const bool _bool;
  BoolExpr(bool b) : _bool(b) {}
  virtual void print(std::ostream& os, int indent);  
};

class NullExpr : public Expr {
public:
  NullExpr() {}
  virtual void print(std::ostream& os, int indent);  
};

class FuncExpr : public Expr {
  std::list<std::string> *_params;
  Stmt *_body;
public:
  FuncExpr(std::list<std::string> *params, Stmt *body) 
    : _params(params), _body(body) {}
  virtual void print(std::ostream& os, int indent);  
};

class AssignExpr : public Expr {
  Expr *_lval, *_rval;
public:
  AssignExpr(Expr *lval, Expr *rval) : _lval(lval), _rval(rval) {}
  virtual void print(std::ostream& os, int indent);  
};

enum ExprOp {
  OR_OP, AND_OP, 
  EQ_OP, NE_OP, LT_OP, LE_OP, GT_OP, GE_OP,
  ADD_OP, SUB_OP, MUL_OP, DIV_OP, MOD_OP,
  NOT_OP, NEG_OP
};

class BinaryExpr : public Expr {
  ExprOp _op;
  Expr *_left, *_right;
public:
  BinaryExpr(ExprOp op, Expr *l, Expr *r) : _op(op), _left(l), _right(r) {}
  virtual void print(std::ostream& os, int indent);  
};

class UnaryExpr : public Expr {
  ExprOp _op;
  Expr *_expr;
public:
  UnaryExpr(ExprOp op, Expr *e) : _op(op), _expr(e) {}
  virtual void print(std::ostream& os, int indent);  
};

class MemberRefExpr : public Expr {
  Expr *_object;
  std::string _field;
public:
  MemberRefExpr(Expr *object, const std::string& field)
    : _object(object), _field(field) {}
  virtual void print(std::ostream& os, int indent);  
};

class ArrayRefExpr : public Expr {
  Expr *_array, *_index;
public:
  ArrayRefExpr(Expr *array, Expr *index) : _array(array), _index(index) {}
  virtual void print(std::ostream& os, int indent);  
};

class CallExpr : public Expr {
  Expr *_func;
  std::list<Expr*> *_args;
public:
  CallExpr(Expr *f, std::list<Expr*> *args)
    : _func(f), _args(args) {}
  virtual void print(std::ostream& os, int indent);  
};

class VarExpr : public Expr {
  const std::string _var;
public:
  VarExpr(const std::string& v) : _var(v) {}
  virtual void print(std::ostream& os, int indent) {os << _var;}
};

#endif // EXPR_H
