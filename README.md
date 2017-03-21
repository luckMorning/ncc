 enum {
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
	ERROR
};

