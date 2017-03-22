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



<program>::={<declaration> | <function_definition>}<eof>

<declaration>::=<var_declaration> <sem> 
               |<function_declaration> <sem>

<var_declaration>::=<type>{star}<id_list><sem> 
                   |<type>{<star>}{<id><assign><value>}<sem>


<function_declaration>::=<type><id><spl><pagram_list><spr>



<type>::=<void>
        |<int>
        |<char>
        |<float>
        |<enum>
        |<struct>


<pagram_list>::={<type><id>{<com><type><id>}}




<function_definition>::=<function_declaration><function_body>

<function_body>::=<bpl>{<var_declaration><sem> | <statement> }<bpr>

<statement>::={<id>}{<assign>}<expression> | <if_statement> | <for_statement> | <return_statement>


<expression>::=


