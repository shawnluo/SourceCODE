
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "color.h"


void print_trace()
{
	my_trace(BRIGHT, GREEN, BLACK, "good\n" );
}



char *Del_Space(char const *str, char *x)
{
	assert(x);
	char *tmp = x;
	while(*str)
	{
		if(*str != ' ')
		{
			*x++ = *str;
		}
		str++;
	}
	x = '\0';


	printf("%s\t", tmp);

	printf("\n");
	return tmp;
}

int main(void)
{
	char *str = "show me the money!";
	char *x = (char *)malloc(16);		//must malloc before string copy
	x = Del_Space(str, x);

	printf("%s\n", x);
	printf("%d\n", (int)strlen(x));


	return 0;
}

