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


char *readfile(char *name);

/*lex anilize
 *file:source file
 */
source  lex( char *file);

#endif
