

GCC=gcc

lex:main.c lex.o
	$(GCC) main.c lex.o token.o -o lex
lex.o:lex.c lex.h token.o 
	$(GCC) -c lex.c 
token.o:token.c token.h
	$(GCC) -c token.c 
clean:
	rm -f lex token.o lex.o 
