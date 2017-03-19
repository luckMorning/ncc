#ifndef _LEX_H_
#define _LEX_H_
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
typedef enum {
	IF, /* if */
	ELSE, /* else */
	FOR, /* for */
	
	VOID, /* void */
	INT, /* int */
	FLOAT,/*float*/
	CHAR,/* char */
	
	RETUEN, /* return */
	BREAK, /* break */
	CONTINUE,/* continue */
	
	INUM, /* 1 2 3 4 5 ...*/
	FNUM, /* 1.0 2.0 3.0 ...*/
	STRING,/* "hello"*/
	CCHAR, /* 'a' */
	
	PLUS, /* '+' */
	SUB, /* '-' */
	STAR,/* '*' */
	DIV, /* '/' */
	MOD, /* '%' */
	
	ULINE,/* '_' */ 
	SIGN, /* '=' */
	EQ, /* '==' */
	NEQ,/* '!=' */
	GT, /* '>' */
	LT, /* '<' */
	GEQ,/* '>=' */
	LEQ,/* '<=' */
	
	SPL, /* '(' */
	SPR,/* ')' */
	MPL,/* '[' */
	MPR,/* ']' */
	BPL,/* '{' */
	BPR,/* '}' */
	
	ID, /*identify */
	ERROR
}var;

typedef struct 
{
	var c;
	int line;
	char value[1024];
}token;

typedef struct {
	char msg[128];
	token *data;
	int count;
	int len;
}token_set;

typedef struct {
    token_set ts;
    int line;
    FILE * file;
    char file_name[256];
}source;




/*initilize tokens list*/
token_set  tokens_init();

/*add token into tokens*/
int tokens_push(token_set * ts, token tk);

/*lex anilize
 *file:source file
 */
source  lex( char *file);

#endif
