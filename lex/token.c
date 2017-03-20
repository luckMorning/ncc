#include "token.h"

token_set tokens_init ()
{
		token_set ts;
		ts.data = NULL;
		ts.count = 0;
		ts.len = 100;
		return ts;
}

int tokens_push(token_set *ts, token tk)
{

    if (ts->data == NULL) {
        ts->data = (token *)malloc(sizeof(token));
        ts->end = ts->data;
        ts->end->next = NULL;
    } else {
        ts->end->next = (token*)malloc(sizeof(token));
        ts->end = ts->end->next;
        ts->end->next = NULL;
    }
    /*copy the value of tk */
    ts->end->c = tk.c;
    ts->end->line = tk.line;
    strcpy(ts->end->value, tk.value);
    /*   */
    ts->count ++;
    return 1;
}
		

