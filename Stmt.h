#ifndef STMT_H
#define STMT_H

#include <iostream>
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
  virtual void print(std::ostream& os, int indent) = 0;  
};

struct NoopStmt : public Stmt {
  virtual void print(std::ostream& os, int indent) {os << ";";}
};

struct ExprStmt : public Stmt {
  Expr *_expr;
  ExprStmt(Expr *e) : _expr(e) {}
  virtual void print(std::ostream& os, int indent) {
    _expr->print(os, indent);
    os << ";";
  }
};

struct BlockStmt : public Stmt {
  std::list<Stmt*> *_stmts;
  BlockStmt(std::list<Stmt*> *stmts) : _stmts(stmts) {}
  virtual void print(std::ostream& os, int indent);
};

struct Var {
  std::string _name;
  Expr *_expr;
  Var(const std::string& n, Expr *e=0) : _name(n), _expr(e) {}
  virtual void print(std::ostream& os, int indent);
};

struct DeclStmt : public Stmt {
  std::list<Var*> *_vars;
  DeclStmt(std::list<Var*> *vars) : _vars(vars) {}
  virtual void print(std::ostream& os, int indent);
};

struct IfStmt : public Stmt {
  Expr *_cond;
  Stmt *_yesStmt, *_noStmt;
  IfStmt(Expr *cond, Stmt *yes, Stmt *no=0) 
    : _cond(cond), _yesStmt(yes), _noStmt(no) {}
  virtual void print(std::ostream& os, int indent);
};

struct WhileStmt : public Stmt {
  Expr *_cond;
  Stmt *_body;
  WhileStmt(Expr *cond, Stmt *body) : _cond(cond), _body(body) {}
  virtual void print(std::ostream& os, int indent);
};

struct ReturnStmt : public Stmt {
  Expr *_expr;
  ReturnStmt(Expr *e=0) : _expr(e) {}
  virtual void print(std::ostream& os, int indent);
};

#endif
