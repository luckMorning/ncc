#include <stdio.h>
#include "../lex/lex.h"

token * tk = NULL;
int line = 1;

void error(char *msg)
{
    printf("error: line:%d note:%s\n",line,msg);
}

void parse_declaration
int syntax (token_set *tks)
{
    tk = tks->data;;
    while (tk->c != END) {
    
        //printf("<%d,%s>\n",tk->c,tk->value);

        if (tk->c == POU) {
            error("不支持#预处理，跳过");
        }else if(tk->c == ENDL) {
            line ++;
            while(tk->c != ENDL) tk = tk->next;
        }
        if (tk->c == SEM)

        tk = tk->next;
    }
    return 0;
}

int main ()
{
    token_set tks = lex("syntax.c");
    return syntax(&tks);
}


