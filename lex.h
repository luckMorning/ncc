#ifndef _LEX_H_
#define _LEX_H_
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "token.h"

typedef struct {
    token_set ts;
    int line;
    FILE * file;
    char file_name[256];
}source;

/*@name file name
 *#return char buffer from name
 */
char *readfile(char *name);


/*@file: sourcefile name
 *#source: deque of token from file
 */
source  lex( char *file);

token next_token(char *s);
#endif
