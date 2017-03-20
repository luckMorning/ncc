#include "lex.h"


source  lex(char *file)
{
    source s;
    return s;
}

char * readfile(char * name)
{
    FILE * f = fopen(name,"r");
    if (f == NULL) return NULL;
    fseek(f,0,SEEK_END);
    int size = ftell(f);
    char * res = (char *)malloc(size);
    if (res == NULL) return NULL;

    rewind(f);
    int pos = 0;
    while (1) {
        char ch = fgetc(f);
        if(feof(f)) break;
        if (ch == '\r') continue;
        res[pos++] = ch;
    }
    res[pos] = 0;
    fclose(f);
    return res;
}

token unexpected(int line,char ch)
{
    token t;
    t.c = ERROR;
    t.line = line;
    sprintf(t.value,"unexpected character: line:%d \'%c\'",line,ch);
    return t;
}

token next_token(char *s)
{
    char ch;
    token t;
    var v;
    static int line = 1;
    char value[125] = {0};
    memset(t.value,0,sizeof(t.value));

    static int pos = 0;
    
    /*skip*/
    while (1) {
        ch = s[pos++];
        if (ch != ' ') {
            if (ch == '\n') {
                line ++;
                continue;
            }
            pos --;
            break;
        }
    }

    while (1) {
        ch = s[pos++];
        if (ch == '+') {
            v = PLUS;
            value[0] = '+';
            break;
        }else if(ch == '-') {
            v = SUB;
            value[0] = '-';
            break;
        }else if (ch == '*') {
            v = MUL;
            value[0] = '*';
            break;
        }else if (ch == '/') {
            v = DIV;
            value[0] = '/';
            break;
        }else if (ch == '%') {
            v = MOD;
            value[0] = '%';
            break;
        }else if (ch == '=') {
            ch = s[pos];/* next char */
            if (ch == '=') {
                v = EQ;
                strcpy(value,"==");
                pos ++;
            }else {
                v = ASSIGN;
                value[0] = '=';
            }
            break;
        }else if (ch == '!') {
            ch = s[pos];
            if (ch == '=') {
                v = NEQ;
                strcpy(value,"!=");
                pos++;
                break;
            }else {
                unexpected(line,s[pos-1]);
                break;
            }
        }else if(ch == '>') {
            char nc = s[pos];
            if (nc == '=') {
                pos++;
                v = GEQ;
                strcpy(value,">=");
                break;
            }else {
                v = GT;
                value[0] = '>';
                break;
            }
        }else if(ch == '<') {
            char nc = s[pos];
            if (nc == '=') {
                pos++;
                v = LEQ;
                strcpy(value,"<=");
                break;
            }else {
                v = LT;
                value[0] = '<';
                break;
            }
        }else if(ch == '\n'){
            line ++;
        }else if (ch == 0 ) {
            v = END;
            strcpy(value,"EOF");
            break;
        }else {
            t = unexpected(line,ch);
            t.line = line;
            return t;
        }
    }

    t.c = v;
    t.line = line;
    strcpy(t.value,value);
    return t;
}


void print_set (token_set* tks)
{
    token * tkp = tks->data;
    int i =0;
    for (;i<tks->count;i++)
    {
        
        printf("<%d,%s>\n",tkp->c,tkp->value);
        tkp=tkp->next;
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
    char *res = readfile(file); 

    while (1)
    {
        tk = next_token(res);
        tokens_push(&tks,tk);
        if (tk.c == END) break;
    }

    
    printf("count of token set : %d\n",tks.count);
    print_set(&tks);


}
