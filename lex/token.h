#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <malloc.h>
#include <stdio.h>

/*all of token */
typedef enum {
	IF,         /* if */
	ELSE,       /* else */
	FOR,        /* for */
	
	VOID,       /* void */
	INT,        /* int */
	FLOAT,      /* float */
	CHAR,       /* char */
    ENUM,       /* enum */
    STRUCT,     /* struct */
	
	RETURN,     /* return */
	BREAK,      /* break */
	CONTINUE,   /* continue */
	
	INUM,       /* 1 2 3 4 5 ...*/
	FNUM,       /* 1.0 2.0 3.0 ...*/
	STRING,     /* "hello"*/
	CCHAR,      /* 'a' */
	
	PLUS,       /* '+' */
	SUB,        /* '-' */
	STAR,        /* '*' */
	DIV,        /* '/' */
	MOD,        /* '%' */

    SPLUS,      /* ++ */
    SSUB,       /* -- */
	
	ULINE,      /* '_' */ 
	ASSIGN,     /* '=' */
	EQ,         /* '==' */
	NEQ,        /* '!=' */
	GT,         /* '>' */
	LT,         /* '<' */
	GEQ,        /* '>=' */
	LEQ,        /* '<=' */

    AND,        /* && */
    OR,         /* || */
	
	SPL,        /* '(' */
	SPR,        /* ')' */
	MPL,        /* '[' */
	MPR,        /* ']' */
	BPL,        /* '{' */
	BPR,        /* '}' */

    DOT,        /* '.' */
    COM,        /* ',' */
    COL,        /* ':' */
    SEM,        /* ';' */
    POU,        /* '#' */
	
	ID,         /*identify */
    ENDL,       /* '\n' */
    END,        /* EOF */
	UNKNOW
}var;

typedef struct _t
{
	var c;
	int line;
	char value[1024];
    struct _t * next;
}token;

typedef struct {
	char msg[128];
	token *data;
    token *end;
	int count;
	int len;
}token_set;

/*initilize tokens list*/
token_set  tokens_init();

/*add token into tokens*/
int tokens_push(token_set * ts, token tk);



#endif
