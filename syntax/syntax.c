#include "syntax.h"

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
            parse_enum();
            return 1;
        case STRUCT:
            get_token();
            parse_struct();
            return 1;
    }
    return 0;
}

void parse_enum()
{}
void parse_struct()
{
    if (tk->c == ID) {

    }
}
void parse_init() 
{}
void parse_declarator()
{}

void parse_declaration ()
{
    if (tk->c == SEM) {
        get_token();
        return;
    }
   
    if (!parse_type()) {
        expect("<type>");
    }

    while (1) {
        parse_declarator();
        if (tk->c == ASSIGN) {
            get_token();
            parse_init(); /* initializer for id */
        }else if (tk->c == BPL) {
            
        }
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

int main (int argc,char *argv[])
{
    if (argc < 2) {
        printf("no input files\n");
        return 1;
    }
    token_set tks = lex(argv[1]);
    return syntax(&tks);
}


