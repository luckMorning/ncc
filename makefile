
lex:lex.c lex.h token.o 
	gcc  lex.c token.o -o lex
token.o:token.c token.h
	gcc -c token.c 
clean:
	rm -f lex token.o 
