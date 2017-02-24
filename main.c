#include <stdio.h>
#include "lex.h"

int main(int argc,char *argv[])
{
		tokens ts = lex(argv[1]);
		int i= 0;
		printf("tokens:%d\n",ts.count);
		for (;i<ts.count;i++) {
			token t= ts.data[i];
			printf("<%d,%s>\n",t.c,t.value);
		}
		printf("%s",ts.msg);
}
