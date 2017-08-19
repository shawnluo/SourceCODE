
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include "math.h"

#include <stdbool.h>
//#include "color.h"

/*
void print_trace()
{
//    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}*/

#if 0

int main(void)
{
/*
	char *p1 = "gooday";
	char *p2 = "yes";

	strcpy(p1, p2);

	printf("%s\n", p1);
*/
	char text[] = "This is a list of lists";
	char *find = "list";
	char *pos = NULL;
	pos = strstr(text, find);
	printf("pos = %s\n", pos);

	strncpy(pos, "text", 4);
	printf("pos = %s\n", pos);
	
	return 0;
}

#else

int main(void)
{
	char *p1 = (char *)malloc(100);
	strcpy(p1, "showmethe");
	printf("%s\n", p1);

/*
	char *p2 = "good";

	strcpy(p1, p2);

	printf("%s\n", p1);*/
	return 0;
}

#endif
