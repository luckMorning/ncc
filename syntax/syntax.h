#ifndef _SYNTAX_H_
#define _SYNTAX_H_
#include <stdio.h>
#include "../lex/lex.h"

void expect(char *msg);
void error(char *msg);

void get_token();
int parse_type();
void parse_enum();
void parse_declarator();
void parse_declaration ();
void parse_struct();
void  parse_init(); /* initializer for id */
int syntax (token_set *tks);
#endif
