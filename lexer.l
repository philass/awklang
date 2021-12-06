%{
  #include "ast.h"
  #include "parser.tab.h"
%}


%%

"&&" { return AND; }
"||" { return OR; }
"<" { return LT; }
">" { return GT; }
"==" { return EQ; }
"{" { return LCURL; }
"}" { return RCURL; }
"BEGIN" { return BEG; }
"END" { return END; }

[0-9]+ { yylval.integer = atoi(yytext); return NUM; }
\$[1-9][0-9]* { yylval.integer = atoi(yytext+1); return POSITIONALARG; }

[ \t\n] { /* IGNORE WHITE SPACE */ }

. { printf("Mystery character %c\n", *yytext); }

%%
