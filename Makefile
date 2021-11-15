parser: lexer.l parser.y
	bison -d parser.y
	flex lexer.l
	cc -o $@ lex.yy.c parser.tab.c -lfl
