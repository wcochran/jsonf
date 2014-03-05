#ifndef STMT_H
#define STMT_H

#include <list>
#include <vector>
#include <map>
#include "Value.h"
#include "Env.h"
#include "Expr.h"

extern int yylineno;

class Stmt {
  const int _lineno;
public:
  Stmt() : _lineno(yylineno) {}
  virtual ~Stmt() {}
  virtual Value *execute(Env *env) = 0;
};

class NoopStmt : public Stmt {
public:
  virtual Value *execute(Env *env);
};

class ExprStmt : public Stmt {
  Expr *_expr;
public:
  ExprStmt(Expr *e) : _expr(e) {}
  virtual Value *execute(Env *env);
};

class BlockStmt : public Stmt {
  std::list<Stmt*> *_stmts;
public:
  BlockState(std::list<Stmt*> *stmts) : _stmts(stmts) {}
  virtual Value *execute(Env *env);
};

struct Var {
  std::string _name;
  Expr *_expr;
  Var(const std::string& n, Expr *e=0) : _name(n), _expr(e) {}
};

class DeclStmt : public Stmt {
  std::list<Var*> *_vars;
public:
  DeclStmt(std::list<Var*> *vars) : _vars(vars) {}
  virtual Value *execute(Env *env);
};

class IfStmt : public Stmt {
  Expr *_cond;
  Stmt *_yesStmt, *_noStmt;
public:
  IfStmt(Expr *cond, Stmt *yes, Stmt *no=0) 
    : _cond(cond), _yesStmt(yes), _noStmt(no) {}
  virtual Value *execute(Env *env);
};

class ReturnStmt : public Stmt {
  Expr *_expr;
public:
  ReturnStmt(Expr *e=0) : _expr(0) {}
  virtual Value *execute(Env *env);
};

#endif
