parser: lexer.l parser.y
	bison -d parser.y
	flex lexer.l
	cc -o $@ lex.yy.c parser.tab.c -lfl

clean:
	-rm parser lex.yy.c parser.tab.c parser.tab.h
