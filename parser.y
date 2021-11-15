%{
#include <stdio.h>
%}

%token NUM
%token POSITIONALARG
%token AND OR GT LT EQ
%token LCURL RCURL
%token BEG END
%token PRINT
%token EOL

%%

statements: /* nothing */
  | statements statement { /*Do something */  }
  ;

statement: pattern LCURL action RCURL { /*Do something  */ }
  ;

pattern: expr { /* Do something */ }
  | BEG { /* Do something */ }
  | END  { /* Do something */ }
  ;

logic: AND
  | OR   { /* Do something */ }   
  | GT   { /* Do something */ }
  | LT   { /* Do something */ }
  | EQ   { /* Do something */ }
  ;

expr: term { /* Do something */ }
  | expr logic term { /* Do something */ }
  ;

term: POSITIONALARG { /* Do something */ }
  | NUM { /* Do something */ }
  ;

action: /* nothing */
  PRINT expr { /* Do something */ }
  ;


%%

int main(int argc, char **arg) {
  yyparse();
}

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}
