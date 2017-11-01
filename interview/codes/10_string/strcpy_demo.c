
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



int main(void)
{
	char *p1, *p2, str[50] = "ABCDEFG";
	p1 = "abcd";
	p2 = "efgh";
	char *x, *y;

	x = strcpy(str + 1, p2 + 1);
	printf("x = %s\t", x);
	printf("str = %s\t", str);
	printf("p2 = %s\n", p2);

	y = strcpy(str + 3, p1 + 3);
	printf("y = %s\t", y);
	printf("str = %s\t", str);
	printf("p1 = %s\n", p1);

	printf("%s\n", strcpy(x, y));
	
	return 0;
}
