
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
	char *data[Row] = {"gooday", "showme", "fine!", "whoare", "getup!"};
#if 0
	char (*pt)[Column] = (char (*)[Column])malloc(sizeof(char) * Column * Row);

	for(int i = 0; i < Row; i++)
	{
		strcpy(*(pt + i), data[i]);
		printf("%s\n", *(pt + i));
	}

	free(pt);
#endif

	char (*pt)[Column] = (char (*)[Column])data[0];//&data[0];

	for(int i = 0; i < Row; i++, pt++)
	{
		pt = (char (*)[Column])data[i];

		printf("%s\n", *pt);
	}	

	return 0;
}
