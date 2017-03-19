#include "lex.h"

int undo(FILE *f)
{
	
	fseek(f,ftell(f)-1,SEEK_SET);
}

token_set tokens_init ()
{
		token_set ts;
		ts.data = (token *)malloc(sizeof(token)*100);
		ts.count = 0;
		ts.len = 100;
		return ts;
}

int tokens_push(token_set *ts, token tk)
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

source  lex(char *file)
{

}

token next_token(FILE * _source)
{
	token t;
	char ch;
	int line = 0;
    while (1) {
	    ch = fgetc(_source);
        if (ch != ' ') break;
    }
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
            strcpy(t.value,"+")
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
				fseek(_source,-1,ftell(_source));
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
				fseek(_source,-1,ftell(_source));
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


void print_set (token_set* tks)
{
    token * tkp = tks->data;
    int i =0;
    for (;i<tks->count;i++)
    {
        
        printf("<%d,%s>\n",tkp[i].c,tkp[i].value);
    }
}

int main ()
{
    token_set tks = tokens_init();
    token tk;
    tk.c = STRING;
    strcpy(tk.value,"hello");
    tk.line = 1;

    char * file = "main.nc";
    FILE * f = fopen(file,"r");
    while (1) {
        tk = next_token(f);
        if (tk.c == ERROR) break;
        tokens_push(&tks,tk);
    }
    fclose(f);

    
    printf("count of token set : %d\n",tks.count);
    print_set(&tks);


}
