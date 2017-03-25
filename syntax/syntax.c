#include "syntax.h"

token * tk = NULL;
int line = 1;

int e = 0;
void expect(char *msg)
{
    e++;
    printf ("line: %d note: expected %s but got %s\n",line,msg,tk->value);
}

void error(char *msg)
{
    e++;
    printf("error: line:%d note:%s\n",line,msg);
}

void get_token()
{
    tk = tk->next;
}



int parse_type()
{
    var v = tk->c;
    if(v == VOID || v == CHAR || v == INT || v == FLOAT)
        return 1;

}


void jump_to(var v)
{
    while (tk->c != v) get_token();
}
void parse_enum()
{}


void parse_struct()
{
    if (tk->c == ID) {

        get_token();
    } else if (tk->c == BPL) {
        get_token();
        while (tk->c != BPR) {
            if (!parse_type()) {
                expect("<类型符>");
            }
            get_token();
            if (tk->c != ID) {
                expect("<标识符>");
            }
            get_token();
            if (tk->c != SEM) {
                expect(";");
            }
        return;
        }
    }else {
        expect("<标识符> or <{>");
    }
    get_token();
}
void parse_init() 
{
    get_token();
    if (tk->c != ASSIGN)
    {
        return;
    }else {
        get_token();
        if(tk->c != CCHAR && tk->c != INUM && tk->c != FNUM && tk->c != STRING && tk->c != ID) {
            expect("<初始值>");
        }else {
            get_token();
        }
    }
}

void parse_declaration ()
{
    if (tk->c == SEM) {
        get_token();
        return;
    }else if (tk->c == POU) {
        printf ("暂时不支持预编译，跳过\n");
        jump_to(ENDL);
        return;
    }else if(tk->c == ENDL) {
        line ++;
        get_token();
        return;
    }
    if( !parse_type()) {
        expect("<类型符>");
    }
    get_token();
    if (tk->c == ID) {
        parse_init();
        if (tk->c != SEM) {
            expect(";");
        }
    }else if (tk->c == BPL) {
        
    }else {
        expect("<id> or '{'");
    }
}
int syntax (token_set *tks)
{
    tk = tks->data;
    while (tk->c != END) {
        //printf("<%d,%s>\n",tk->c,tk->value);
        parse_declaration();
    }
    return !e;
}

int main (int argc,char *argv[])
{
    if (argc < 2) {
        printf("no input files\n");
        return 1;
    }
    token_set tks = lex(argv[1]);
    if (syntax(&tks)) {
        printf("语法分析ok!\n");
    }
    return 0;
}


