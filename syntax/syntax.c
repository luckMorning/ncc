#include "syntax.h"

token * tk = NULL;
int line = 1;
int l = 0;
int e = 0;
int syn_level = 0;

void slog (char *msg)
{
    if (l)
    printf ("%s",msg);
}
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

void tab()
{
    int i = 0;
    for(i=0;i<syn_level;i++) {
        printf("    ");
    }
}
void out()
{
   if (tk->c == ENDL)  {
        printf("\n");
        if (tk->next->c == BPR) {
            syn_level --; 
        }
        tab();
    }else if (tk->c == BPL) {
        printf("%s ",tk->value);
        syn_level ++;
    }else {
        printf("%s ",tk->value);
    }
 
}

void get_token()
{
     
    out();
    tk = tk->next;
}



int parse_type()
{
    var v = tk->c;
    if(v == VOID || v == CHAR || v == INT || v == FLOAT || v == STRING) {
        get_token();
        while (tk->c == MPL) {
            get_token();
            if (tk->c != MPR) {
                expect("']'");
            }else {
                get_token();
            }
        }
        return 1;
    }
    else 
        return 0;

}


void jump_to(var v)
{
    while (tk->c != v) get_token();
}
void parse_enum()
{}

void parse_pagram()
{
    get_token();
    while(tk->c != SPR){ 
        printf("参数");
        if (!parse_type()) {
            expect("<type>");
        }
        if (tk->c == ID) {
            parse_init();
        }else {
            expect("id");
        }
        if (tk->c != SPR ) {
            if (tk->c != COM) {
                expect(",");
            }else {
                get_token();
            }
        }
    }
    get_token();
}
void parse_funcbody()
{
    jump_to(BPR);
    get_token();
}


void parse_init() 
{
    if (tk->c == ID) {
        get_token();
    }else {
        expect("<id>");
    }

     if (tk->c == ASSIGN)
    {
        get_token();
        if(tk->c != CCHAR && tk->c != INUM && tk->c != FNUM && tk->c != CSTRING && tk->c != ID) {
            expect("<初始值>");
        } else
            get_token();
    }else 
        return;

    
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
        expect("<type>");
    }

    
    if (tk->c == ID) {
        slog("碰到id,解析初始化");
        parse_init();
        if (tk->c == SEM) {
            get_token();
            return;
        }else if (tk->c == SPL){
            slog("左小括号，函数参数解析");
            parse_pagram();
            if (tk->c == SEM) 
                return;
            slog("函数体解析");
            parse_funcbody();
            return;
        }else if ( tk->c == COM ) {
            while (tk->c == COM) {
                get_token();
                parse_init();
            }
            if(tk->c != SEM) expect(";");
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


