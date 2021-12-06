%{
#include <stdio.h>
#include "ast.h"

struct ast* result;

%}


%union {
 enum logicOp logicOpT;
 struct ast* astT;
 struct pattern* patternT;
 struct action* actionT;
 struct exp* expT;
 struct term* termT;
 int integer;
}

%token <integer> NUM;
%token <integer> POSITIONALARG;
%token AND OR GT LT EQ;
%token LCURL RCURL;
%token BEG END;
%token PRINT;
%token EOL;

%type <astT> statement
%type <patternT> pattern
%type <actionT> action
%type <expT> expr
%type <termT> term
%type <logicOpT> logic

%%

//statements: /* nothing */
//  | statements statement { /*Do something */  }
//  ;
//

statement: pattern LCURL action RCURL { 
                                        result = newStatement($1, $3);
                                        astWalk(result);
                                      }
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
  | expr logic expr { $$ = newExpr($1, $2, $3); }
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
  expr { $$ = newAction($1); }
  ;


%%

int main(int argc, char **arg) {
  int res = yyparse();
  printf("yyparse result is %d\n", res);
  printf("finished the parsing\n");
}

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);


}
