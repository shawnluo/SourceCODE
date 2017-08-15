
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "color.h"



#define Row       5
#define Column    7

void fun(int k, int *p)
{
    int a, b;

    if (k == 1 || k == 2)
    {
        *p = 1;
    }
    else
    {
        fun(k - 1, &a);
        fun(k - 2, &b);
        *p = a + b;
    }
}


//beware the parament and return value! just a copy or ...?
char *Del_Space(char const *str)
{
//	char *p = str;

	while(1)
	{
		
	}
}

int main(void)
{
	char *str = "show me the money!";
	char *x = (char *)malloc(100);
//	char *p = Del_Space(str);
	strcpy(x, str);

	my_trace(BRIGHT, GREEN, BLACK, "good\n" );
	return 0;
}

