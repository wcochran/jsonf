%{
#include <cstring>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include "Expr.h"
#include "Stmt.h"
#include "jsonf.tab.hpp"   // created bison -d jsonf.ypp

extern void yyerror(const char *);
%}

%option noyywrap
%option nounput
%option noinput

%%

true                     {return TRUE;}
false                    {return FALSE;}
null                     {return NULL_;}
func                     {return FUNC;}
var                      {return VAR;}
if                       {return IF;}
else                     {return ELSE;}
while                    {return WHILE;}
return                   {return RETURN;}
\"[^"]*\"                {yylval.cstr = strdup(yytext); return STRING;}
[a-zA-Z_][a-zA-Z_0-9]*   {yylval.cstr = strdup(yytext); return IDENT;}
[0-9]*(\.[0-9]+)?        {yylval.num = atof(yytext); return NUM;}
"||"                     {return OR;}
"&&"                     {return AND;}
"=="                     {return EQ;}
"!="                     {return NE;}
"<="                     {return LE;}
">="                     {return GE;}
[-+*/%<>=!:,;.\[\](){}]  {return yytext[0];}
[ \t\f\r\v]              { ; }
[\n]                     {yylineno++;}
.                        {yyerror("unknown lexeme!");}      

%%
