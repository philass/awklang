parser: lexer.l parser.y
	bison -d parser.y
	flex lexer.l
	cc -o ast.o -c ast.c
	cc -o $@ ast.o lex.yy.c parser.tab.c -lfl

clean:
	-rm parser lex.yy.c parser.tab.c parser.tab.h
