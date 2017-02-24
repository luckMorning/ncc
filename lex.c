#include "lex.h"

int undo(FILE *f)
{
	
	fseek(f,ftell(f)-1,SEEK_SET);
}

tokens tokens_init ()
{
		tokens ts;
		ts.data = (token *)malloc(sizeof(token)*100);
		ts.count = 0;
		ts.len = 100;
		return ts;
}

int tokens_push(tokens *ts, token tk)
{
		if (ts-> count == ts->len) {
			token * data = (token *)malloc(sizeof(token)*(ts->len +100));
			memcpy(data,ts->data,ts->count*sizeof(token));	
			free(ts->data);
			ts->data = data;
			ts->len += 100;
		}
		token t;
		t.c = tk.c;
		strcpy(t.value, tk.value);
		
		ts->data[ts->count] = t;
			ts->count ++;
}

tokens  lex(char *file)
{
	_source = fopen(file,"r");
	tokens ts = tokens_init();
	ts.count = 0;
	if (_source == NULL) {
		char msg[512] = {0};
		sprintf(msg,"can't open file \'%s\'",file);
		strcpy(ts.msg, msg);
		return ts;
	}
	
	while (!feof(_source)) {
		token t = next_token();
		if (t.c != ERROR)
		tokens_push(&ts,t);	
	}
	
	fclose(_source);
	_source = NULL;
	strcpy(ts.msg,"lex ok!");
	return ts;
}

token next_token()
{
	token t;
	char ch;
	int line = 0;;
		ch = fgetc(_source);
	switch (ch ) {
		case ' ':  {
			break;
		}
		case '\n': {
			line ++;
			break;
		}
		case '+': 	{
			t.c = PLUS;
			t.line = line;
			return t;		
		}
		case '-': {
			t.c = SUB,
			t.line = line;
			return t;
		}
		case '*':{
			t.c = STAR;
			t.line = line;
			return t;	
		}
		case '/': {
			t.c = DIV;
			t.line = line;
			return t;	
		}
		case '%': {
			t.c = MOD;
			t.line = line;
			return t;	
		}
		case '=': {
			char nc = fgetc(_source);
			if (nc == '=') {
				t.c = EQ;	
			}else {
				undo(_source);
				t.c = SIGN;	
			}	
			t.line = line;
			return t;
		}
		case '!': {
			char c = fgetc(_source);	
			if (c == '=') {
				t.c = NEQ;
				t.line = line;
				return t;
			}else {
				undo(_source);
				t.c = ERROR;
				t.line = line;
				return t;
			}
		}
		case '(': {
			t.c = SPL;
			t.line = line;
			return t;	
		}
		case ')': {
			t.c = SPR;
			t.line = line;
			return t;	
		}
		case '[': {
			t.c = MPL;
			t.line = line;
			return t;	
		}
		case ']': {
			t.c = MPR;
			t.line = line;
			return t;	
		}
		case '{': {
			t.c = BPL;
			t.line = line;
			return t;	
		}
		
		case '}': { 
			t.c = BPR;
			t.line = line;
			return t;
		}
		case '\'': {
			char v = fgetc(_source);
			char n = fgetc(_source);
			if (n == '\'') {
			t.c = CCHAR;
			t.value[0] = v;
			t.value[1] =0;
			}else {
				t.c = ERROR;	
				strcpy(t.value,"constant char expect : \'");
			}
			t.line = line;
			return t;
		}
		case '\"': {
			char n;
			int i=0;
			while ((n = fgetc(_source)) != '\"') 
			{
				if (n == EOF) {
					t.c = ERROR;
					t.line = line;
					strcpy(t.value,"constant string expect: \"");
					return t;	
				}
				t.value[i++] = n;
			}	
			t.c = STRING;
			t.line = line;
			return t;
		}
		default:
		t.c = ERROR;
		t.line = line;
		return t;			
	}
	return t;	
}
