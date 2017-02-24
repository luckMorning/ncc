#ifndef _LEX_H_
#define _LEX_H_
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
typedef enum {
	IF,
	ELSE,
	FOR,
	
	VOID,
	INT,
	FLOAT,
	CHAR,
	
	RETUEN,
	BREAK,
	CONTINUE,
	
	INUM,
	FNUM,
	STRING,
	CCHAR,
	
	PLUS, //+
	SUB, //-
	STAR,//
	DIV,
	MOD,
	
	ULINE,//'_'
	SIGN,
	EQ,
	NEQ,
	BT,
	ST,
	BEQ,
	SEQ,
	
	SPL,
	SPR,
	MPL,
	MPR,
	BPL,
	BPR,
	
	ID,
	ERROR,	
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
}tokens;


FILE *_source;

/*undo getc of file*/
int undo(FILE *f);

/*return next token*/
token next_token(); 

/*initilize tokens list*/
tokens  tokens_init();

/*add token into tokens*/
int tokens_push(tokens * ts, token tk);

/*lex anilize
 *file:source file
 */
tokens lex( char *file);

#endif
