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
        if (ch == EOF) {
            res[pos] = 0;
            break;
        }
        if (ch == '\r') continue;
        res[pos] = ch;
    }
    fclose(f);
    return res;
}

void unget(FILE* f) 
{
    int pos = ftell(f);
    rewind(f);
    fseek(f,pos-1,SEEK_SET);
}

token next_token(FILE * s)
{
    char ch;
    token t;
    ch = fgetc(s);
    printf("[%c ",ch);
    unget(s);
    ch = fgetc(s);
    printf("%c] \n",ch);
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
    tokens_push(&tks,tk);
    tokens_push(&tks,tk);

    char * file = "main.nc";
    char *res = readfile(file); 
    if (res)
    printf("res;%s\n",res);

    
    printf("count of token set : %d\n",tks.count);
    print_set(&tks);


}
