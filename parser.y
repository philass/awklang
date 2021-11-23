%{
#include <stdio.h>
#include "ast.h"


%}

%token NUM
%token POSITIONALARG
%token AND OR GT LT EQ
%token LCURL RCURL
%token BEG END
%token PRINT
%token EOL

%%

//statements: /* nothing */
//  | statements statement { /*Do something */  }
//  ;
//

statement: pattern LCURL action RCURL { $$ = newStatement($1, $3); }
  ;

pattern: expr { $$ = newPattern($1); }
  | BEG { $$ = newPatternBegin(); }
  | END  { $$ = newPatternEnd(); }
  ;

logic: AND 
  {
    enum logicOp operation = ANDOp;
    return operation;
  }
  | OR
  {
    enum logicOp operation = OROp;
    return operation;
  }

  | GT
  {
    enum logicOp operation = GTOp;
    return operation;
  }
  | LT
  {
    enum logicOp operation = LTOp;
    return operation;
  }
  | EQ
  {
    enum logicOp operation = EQOp;
    return operation;
  }
  ;

expr: term { $$ = newExprTerm($1); }
  | expr logic term { $$ = newExpr($1, $2, $3); }
  ;

term: POSITIONALARG 
  { 
    $$ = newTerm(Positional, $1);
  }
  | NUM 
  { 
    $$ = newTerm(Constant, $1);
  }
  ;

action: /* nothing */
  //PRINT expr { /* Do something */ }
  expr { newAction($1); }
  ;


%%

int main(int argc, char **arg) {
  yyparse();
}

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}
