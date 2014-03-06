#ifndef STMT_H
#define STMT_H

#include <list>
#include <vector>
#include <map>
#include "Value.h"
#include "Env.h"
#include "Expr.h"

extern int yylineno;

struct Stmt {
  const int _lineno;
  Stmt() : _lineno(yylineno) {}
  virtual ~Stmt() {}
};

struct NoopStmt : public Stmt {
};

struct ExprStmt : public Stmt {
  Expr *_expr;
  ExprStmt(Expr *e) : _expr(e) {}
};

struct BlockStmt : public Stmt {
  std::list<Stmt*> *_stmts;
  BlockStmt(std::list<Stmt*> *stmts) : _stmts(stmts) {}
};

struct Var {
  std::string _name;
  Expr *_expr;
  Var(const std::string& n, Expr *e=0) : _name(n), _expr(e) {}
};

struct DeclStmt : public Stmt {
  std::list<Var*> *_vars;
  DeclStmt(std::list<Var*> *vars) : _vars(vars) {}
};

struct IfStmt : public Stmt {
  Expr *_cond;
  Stmt *_yesStmt, *_noStmt;
  IfStmt(Expr *cond, Stmt *yes, Stmt *no=0) 
    : _cond(cond), _yesStmt(yes), _noStmt(no) {}
};

struct WhileStmt : public Stmt {
  Expr *_cond;
  Stmt *_body;
  WhileStmt(Expr *cond, Stmt *body) : _cond(cond), _body(body) {}
};

struct ReturnStmt : public Stmt {
  Expr *_expr;
  ReturnStmt(Expr *e=0) : _expr(0) {}
};

#endif
