all: parser

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser: lex.yy.c parser.tab.c parser.tab.h symbolTable.h AST.h
	gcc -o parser parser.tab.c lex.yy.c
	./parser testProg.cmm

clean:
	rm -f parser lexer parser.tab.c lex.yy.c parser.tab.h parser.output IRcode.ir
	ls -l

access: lexer.l parser.y testProg.cmm AST.h symbolTable.h IRcode.h stack.h
	chmod 700 lexer.l
	chmod 700 parser.y
	chmod 700 testProg.cmm
	chmod 700 AST.h	
	chmod 700 symbolTable.h
	chmod 700 IRcode.h
	chmod 700 stack.h
this:
	make clean
	make parser
	
