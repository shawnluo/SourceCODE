#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char s[5]={'s','a','\0','c','h'};
    char p[5];
    char t[5];
    strcpy(p,s);
    memcpy(t,s,5);
    printf("sachin p is [%s], t is [%s]",p,t);
	
    return 0;
}


