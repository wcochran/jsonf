#ifndef EXPR_H
#define EXPR_H

#include <list>
#include <vector>
#include <map>
#include "Value.h"
#include "Env.h"

class Stmt;

extern int yylineno;

class Expr {
  const int _lineno;
  Value *_cachedValue;
public:
  Expr() : _lineno(yylineno), _cachedValue(0) {}
  virtual ~Expr() {delete _cachedValue;}
  virtual Value *eval(Env *env) = 0;
};

struct Member {
  const int _lineno;
  const std::string _name;
  Expr *_expr;
  Member(const std::string& n, Expr *e) 
    : _lineno(yylineno), _name(n), _expr(e) {}
  ~Member() {delete _expr;}
};

class ObjectExpr : public Expr {
  std::list<Member*> *_members;
  std::map<string,Expr*> _table;
public:
  ObjectExpr() : _members(0), _table() {}
  virtual ~ObjectExpr();
  ObjectExpr(std::list<Member*> *members) : _members(*members), _table() {
    std::list<Member*>::iterator iter = _members->begin();
    while (iter != _members->end()) {
      _table[(*iter)->_name] = (*iter)->_expr;
      ++iter;
    }
  }
  Expr *lookup(const std::string* n) {
    std::map<string,Expr*>::iterator iter = _table->find(n);
    return (iter == _table->end()) ? 0 : iter->second;
  }
  virtual Value *eval(Env *env);
};

class ArrayExpr : public Expr {
  std::list<Expr*> *_elems;
  std::vector<Expr*> _array;
public:
  ArrayExpr() : _elems(0), _array() {}
  virtual ~ObjectExpr();
  ArrayExpr(std::list<Expr*> *elems) : _elems(elems), _array(*elems) {}
  Expr *index(int i) {return _array[i];}
  size_t size() const {return _array.size();}
  virtual Value *eval(Env *env);
};

class StringExpr : public Expr {
public:
  const std::string str;
  StringExpr(const std::string& s) : str(s) {}
  virtual Value *eval(Env *env);
};

class NumberExpr : public Expr {
public:
  const double num;
  NumberExpr(double n) : num(n) {}
  virtual Value *eval(Env *env);
};

class BoolExpr : public Expr {
public:
  const bool val;
  BoolExpe(bool v) : val(b) {}
  virtual Value *eval(Env *env);
};

class NullExpr : public Expr {
public:
  NullExpr(bool v) {}
  virtual Value *eval(Env *env);
};

class FuncExpr : public Expr {
  std::list<std::string> *_params;
  Stmt *_body;
public:
  FuncExpr(std::list<std::string> *params, Stmt *body) 
    : _params(params), _body(body) {}
  virtual ~FuncExpr() {delete _params; delete _body;}
  Value *call(const std::list<Expr*>& actuals);
  virtual Value *eval(Env *env);
};

class AssignExpr : public Expr {
  Expr *_lval, *_rval;
public:
  AssignExpr(Expr *lval, Expr *rval) : _lval(lval), _rval(rval) {}
  virtual ~AssignExpr() {delete _lval; delete _rval;}
  virtual Value *eval(Env *env);
};

enum ExprOp {
  OR_OP, AND_OP, 
  EQ_OP, NE_OP, LT_OP, LE_OP, GT_OP, GE_OP,
  ADD_OP, SUB_OP, MUL_OP, DIV_OP, MOD_OP,
  NOT_OP, NEG_OP
};

class BinaryExpr : public Expr {
  ExprOp _op;
  Expr *_left, *right;
public:
  BinaryExpr(ExprOp op, Expr *l, Expr *r) : _op(op), _left(l), _right(r) {}
  virtual ~BinaryExpr() {delete _left; delete _right;}
  virtual Value *eval(Env *env);
};

class UnaryExpr : public Expr {
  ExprOp _op;
  Expr *_expr;
public:
  UnaryOp(ExprOp op, Expr *e) : _op(op), _expr(e) {}
  virtual ~UnaryOp() {delete _expr;}
  virtual Value *eval(Env *env);
};

class MemberRefExpr : public Expr {
  Expr *_object;
  std::string _field;
public:
  MemberRefExpr(Expr *object, const std::string& field)
    : _object(object), _field(field) {}
  virtual ~MemberRefObject() {delete _object;}
  virtual Value *eval(Env *env);
};

class ArrayRefExpr : public Expr {
  Expr *_array, Expr *_index;
public:
  ArrayRefExpr(Expr *array, Expr *index) 
    : _array(object), _index(index) {}
  virtual ~ArrayRefObject() {delete _array; delete _index;}
  virtual Value *eval(Env *env);
};

class CallExpr : public Expr {
  Expr *_func;
  std::list<Expr*> *_args;
public:
  CallExpr(Expr *f, std::list<Expr*> *args)
    : _func(f), _args(args) {}
  virtual ~CallExpr();
  virtual Value *eval(Env *env);
};

#endif // EXPR_H
