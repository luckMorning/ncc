#include <stdio.h>
#include "lex.h"

int main (int argc,char *argv[])
{
    if (argc < 2) {
        printf("no input files\n");
        return 0;
    }
   
    token_set tks = lex(argv[1]);   
    printf("count of token set : %d\n",tks.count);
    print_set(&tks);

    return 0;
}
