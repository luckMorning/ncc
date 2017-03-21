#include <stdio.h>
#include "../lex/lex.h"

token * tk = NULL;
int line = 1;

void expect(char *msg)
{
    printf ("expected: %s\n",msg);
}

void error(char *msg)
{
    printf("error: line:%d note:%s\n",line,msg);
}

void get_token()
{
    tk = tk->next;
}



int parse_type()
{
    switch (tk->c) {
        case VOID:
        case CHAR:
        case INT:
        case FLOAT:
            get_token();
            return 1;
        case ENUM:
            get_token();
        case STRUCT:
            get_token();
            return parse_struct();
    }
    return 0;
}



void parse_declaration ()
{
    if (!parse_type()) {
        expect("<type>");
        get_token();
    }
    if (tk->c == SEM) {
        get_token();
    }

}
int syntax (token_set *tks)
{
    tk = tks->data;
    while (tk->c != END) {
        //printf("<%d,%s>\n",tk->c,tk->value);
        parse_declaration();
    }
    return 0;
}

int main ()
{
    token_set tks = lex("syntax.c");
    return syntax(&tks);
}


