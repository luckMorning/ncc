#include "lex.h"


token_set lex(char *file)
{
    token_set ts = tokens_init();
    token tk;
    char *res = readfile(file); 
    if (res == NULL)  return ts;
    while (1)
    {
        tk = next_token(res);
        if (tk.c == UNKNOW) printf("unknow:line:%d note:%s\n",tk.line,tk.value);
        tokens_push(&ts,tk);
        if (tk.c == END) break;
    }
    return ts;
}

char turn_c (char ch)
{
    switch(ch) {
    case '\'':
        return '\'';
    case 't':
        return '\t';
    case 'n':
        return '\n';
    case '\"':
        return '\"';
    case '0':
        return '\0';
    case 'f':
        return '\f';
    case 'b':
        return '\b';
    case 'r':
        return '\r';
    case 'v':
        return '\v';
defalut:
        return ch;
    }
    return ch;
}

char * readfile(char * name)
{
    FILE * f = fopen(name,"r");
    if (f == NULL) return NULL;
    fseek(f,0,SEEK_END);
    int size = ftell(f);
    char * res = (char *)malloc(size);
    if (res == NULL) return NULL;

    rewind(f);
    int pos = 0;
    while (1) {
        char ch = fgetc(f);
        if(feof(f)) break;
        if (ch == '\r') continue;
        res[pos++] = ch;
    }
    res[pos] = 0;
    fclose(f);
    return res;
}

void unknow_c(int line,char* ch)
{

    printf("unknow character: line:%d \'%s\'",line,ch);
}

token next_token(char *s)
{
    char ch;
    token t;
    var v;
    static int line = 1;
    char value[125] = {0};
    memset(t.value,0,sizeof(t.value));

    static int pos = 0;
    
    /*skip*/
    while (1) {
        ch = s[pos++];
        if (ch != ' ' && ch != '\t') {
            if (ch == '/') {
                if(s[pos] == '*') {
                    pos = strstr(s+pos,"*/") -s + 2; 
                    continue;
                } 
                if(s[pos] == '/') {
                    pos = strstr(s+pos,"\n") -s +1;
                    line ++;
                    continue;
                }
            }
            
            pos --;
            break;
        }
    }


        ch = s[pos++];
        if (ch == '+') {
            char nc = s[pos];
            if (nc == '+') {
                pos ++;
                v = SPLUS;
                strcpy(value,"++");
            }else {
                v = PLUS;
                value[0] = '+';
            }
        }else if(ch == '-') {
            char nc = s[pos];
            if (nc == '-') {
                pos ++;
                v = SSUB;
                strcpy(value,"--");
            }else {
                v = SUB;
                value[0] = '-';
            }
        }else if (ch == '*') {
            v = STAR;
            value[0] = '*';
        }else if (ch == '/') {
            v = DIV;
            value[0] = '/';
        }else if (ch == '%') {
            v = MOD;
            value[0] = '%';
        }else if (ch == '(') {
            v = SPL;
            value[0] = '(';
        }else if (ch == ')') {
            v = SPR;
            value[0] = ')';
        }else if (ch == '[') {
            v = MPL;
            value[0] = '[';
        }else if(ch == ']') {
            v = MPR;
            value[0] = ']';
        }else if(ch == '{') {
            v = BPL;
            value[0] = '{';
        }else if(ch == '}') {
            v = BPR;
            value[0] = '}';
        }else if (ch == '.') {
            v = DOT;
            value[0] = '.';
        }else if (ch == ':') {
            v = COL;
            value[0] = ':';
        }else if (ch == ';') {
            v = SEM;
            value[0] = ';';
        }else if (ch == ',') {
            v = COM;
            value[0] = ',';
        }else if (ch == '#') {
            v =POU;
            value[0] = ch;
        }else if (ch == '=') {
            ch = s[pos];/* next char */
            if (ch == '=') {
                v = EQ;
                strcpy(value,"==");
                pos ++;
            }else {
                v = ASSIGN;
                value[0] = '=';
            }
        }else if (ch == '!') {
            ch = s[pos];
            if (ch == '=') {
                v = NEQ;
                strcpy(value,"!=");
                pos++;
            }else {
                v = UNKNOW;
                value[0] = ch;
            }
        }else if(ch == '>') {
            char nc = s[pos];
            if (nc == '=') {
                pos++;
                v = GEQ;
                strcpy(value,">=");
            }else {
                v = GT;
                value[0] = '>';
            }
        }else if(ch == '<') {
            char nc = s[pos];
            if (nc == '=') {
                pos++;
                v = LEQ;
                strcpy(value,"<=");
            }else {
                v = LT;
                value[0] = '<';
            }
        }else if (ch == '&') {
            char nc = s[pos];
            if (nc == '&') {
                v = AND;
                strcpy(value,"&&");
                pos ++;
            }else {
                v = UNKNOW;
                value[0] = ch;
            }
        }else if (ch == '|') {
            char nc = s[pos];
            if (nc == '|') {
                v = OR;
                strcpy(value,"||");
                pos ++;
            }else {
                v = UNKNOW;
                value[0] = ch;
            }
        }else if (ch == '\'') {
            char nc = s[pos+1];
             
            if (nc != '\'' ||  s[pos] == '\\') {
                if (s[pos] == '\\' && s[pos+2] == '\'') {
                    v = CCHAR;
                    value[0] = turn_c(nc);
                    pos += 3;

                }
            }else{
                v = CCHAR;
                value[0] = s[pos];
                pos += 2;
            }
        }else if (ch == '\"') {
            
            char temp[1024] = {0};
            int tempi = 0;
            int t = 0;
            while (1) {
        
                char idc = s[pos++];
                if (idc == '\n') line ++;
                if (idc == '\\') {
                    t = 1;
                    continue;
                } 
                if (t) {
                    idc = turn_c(idc);
                    t = 0;
                }
                if (idc == '\"' && !t) break;
                temp[tempi++] = idc;
            }
            v = STRING;
            strcpy(value,temp);
        
        }else if ( (ch >= 'A' && ch <= 'Z' ) || ch == '_' || (ch >= 'a' && ch <= 'z')) {
            pos --;
            char temp[256] = {0};
            int tempi = 0;
            while (1) {
                char idc = s[pos++];
                if (idc == ' ') break;
                if ((idc >= 'A' && idc <= 'Z' ) || (idc>='a'&&ch<='z') || idc == '_' || (idc >= '0' && idc <= '9')){
                    temp[tempi++] = idc;
                }else{
                    pos --;
                    break;
                }
            }

        
            strcpy(value,temp);
            /* parse key word */
            if (!strcmp(value,"if")) {
                v = IF;
            }else if( !strcmp(value,"else") ) {
                v = ELSE;
            }else if(!strcmp(value,"for")) {
                v = FOR;
            }else if(!strcmp(value,"void")) {
                v = VOID;
            }else if(!strcmp(value,"char")) {
                v = CHAR;
            }else if(!strcmp(value,"int")) {
                v = INT;
            }else if(!strcmp(value,"float")) {
                v = FLOAT;
            }else if(!strcmp(value,"enum")) {
                v = ENUM;
            }else if(!strcmp(value,"struct")) {
                v = STRUCT;
            }else if(!strcmp(value,"break")) {
                v = BREAK;
            }else if(!strcmp(value,"continue")) {
                v = CONTINUE;
            }else if(!strcmp(value,"return")) {
                v = RETURN;
            }else {
                v = ID;
            }
        }else if (ch >= '0' && ch <= '9') {
            pos --;
            int ti = 0;
            int have_point = 0;
            while (1) {
                char tc = s[pos++];
                if (tc == ' ' || tc == '\n') {
                    if (tc == '\n') {
                        line ++;
                    }
                    break;
                }
                if ((tc >= '0' && tc <= '9') || tc == '.')  {
                    if (tc == '.') {
                        if (!have_point) {
                            have_point = 1;
                        }else {
                            v = UNKNOW;
                            value[0] = tc;
                            break;
                        }
                    }
                    value[ti++] = tc;
                }else {
                    break;
                }
            }
            if (have_point) {
                v = FNUM; 
            }else {
                v = INUM;
            }
        }else if(ch == '\n'){
            line ++;
            v = ENDL;
            strcpy(value,"endl");
        }else if (ch == 0 ) {
            v = END;
            strcpy(value,"EOF");
            
        }else {
            v = UNKNOW;
            value[0] = ch;
        }
    

    t.c = v;
    t.line = line;
    strcpy(t.value,value);
    return t;
}


void print_set (token_set* tks)
{
    token * tkp = tks->data;
    int i =0;
    for (;i<tks->count;i++)
    {
        
        printf("<%d,%s>\n",tkp->c,tkp->value);
        tkp=tkp->next;
    }
}


