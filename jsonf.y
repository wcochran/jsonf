%token STRING
%token IDENT
%token NUMBER
%token TRUE FALSE NULL
%token FUNC VAR IF ELSE WHILE RETURN

%right '='
%left OR
%left AND
%nonassoc EQ NE
%nonassoc '<' LE '>' GE
%left '-' '+'
%left '*' '/' '%'
%right '!'
%left '.' '[' '('

%expect 1

%%

start : object
      ;

object : '{' '}'
       | '{' members '}'
       ;

members : pair
        | members ',' pair
        ;

pair : STRING ':' expr
     | IDENT ':' expr
     ;

array : '[' ']'
      | '[' elements ']'
      ;

elements : expr
         | elements ',' expr
         ;

value : STRING
      | NUMBER
      | object
      | array
      | TRUE
      | FALSE
      | NULL
      | func
      ;

func : FUNC params block_stmt
     ;

params : '(' ')'
       | '(' formals ')'
       ;

formals : IDENT
        | formals ',' IDENT
        ;

stmt : ';'
     | block_stmt
     | decl
     | expr ';'
     | if_stmt
     | while_stmt
     | return_stmt
     ;

block_stmt : '{' stmts '}'
           ;

stmts : stmt
      | stmts stmt
      ;

decl  : VAR vars ';'
      ;

vars : var
     | vars ',' var
     ;

var : IDENT
    | IDENT '=' expr
    ;

if_stmt : IF '(' expr ')' stmt
        | IF '(' expr ')' stmt ELSE stmt
        ;

while_stmt : WHILE '(' expr ')' stmt
           ;

return_stmt : RETURN expr ';'
            | RETURN ';'
            ;

expr : expr '=' expr
     | expr OR expr
     | expr AND expr
     | expr EQ expr
     | expr NE expr
     | expr '<' expr
     | expr LE expr
     | expr '>' expr
     | expr GE expr
     | expr '+' expr
     | expr '-' expr
     | expr '*' expr
     | expr '/' expr
     | expr '%' expr
     | '!' expr
     | '-' expr  %prec '!'
     | '+' expr  %prec '!'
     | '(' expr ')'
     | expr '.' IDENT
     | expr '[' expr ']'
     | expr '(' args ')'
     | IDENT
     | value
     ;

args : 
     | actuals
     ;

actuals : expr
        | actuals ',' expr
        ;

%%
