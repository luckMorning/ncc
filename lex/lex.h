#ifndef _LEX_H_
#define _LEX_H_
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "token.h"


/*@name file name
 *#return char buffer from name
 */
char *readfile(char *name);


/*@file: sourcefile name
 *#source: deque of token from file
 */
token_set  lex( char *file);

token next_token(char *s);

void print_set(token_set * tks);
#endif
