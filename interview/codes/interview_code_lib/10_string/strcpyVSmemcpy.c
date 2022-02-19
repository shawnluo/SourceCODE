
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


void dump5(char *str)
{
    char *p = str;
	int n;

    for (n = 0; n < 5; ++n)
    {
        printf("%2.2x ", *p);
        ++p;
    }
    printf("\t");

    p = str;
    for (n = 0; n < 5; ++n)
    {
        printf("%c", *p ? *p : ' ');
        ++p;
    }
    printf("\n", str);
}

int main()
{
    char s[5] = { 's', 'a', '\0', 'c', 'h' };

    char membuff[5];
    char strbuff[5];

    memset(membuff, 0, 5);
    memset(strbuff, 0, 5);

    memcpy(membuff, s, 5);		//will copy everything
    strcpy(strbuff, s);			//will copy until meet '\0'

    dump5(membuff); // show what happened
    dump5(strbuff);

    return 0;
}

