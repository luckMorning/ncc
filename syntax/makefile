
syntax:syntax.c  lex.o token.o
	gcc syntax.c lex.o token.o -o syntax 
lex.o:../lex/lex.c ../lex/lex.h 
	gcc -c ../lex/lex.c
token.o:../lex/token.c ../lex/token.h
	gcc -c ../lex/token.c
