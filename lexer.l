%{
  #include "parser.tab.h"
%}


%%

"&&" { return AND; }
"||" { return OR; }
"<" { return LT; }
">" { return GT; }
"==" { return EQ; }

"BEGIN" { return BEG; }
"END" { return END; }

"[0-9]+" { yylval = atoi(yytext); return NUM; }
"$[1-9][0-9]+" { yylval = atoi(yytext); return POSITIONALARG; }

[ \t\n] { /* IGNORE WHITE SPACE */ }

. { printf("Mystery character %c\n", *yytext); }

%%
