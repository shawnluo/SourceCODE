
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

	char (*pt)[Column];
	pt = (char (*)[Column])malloc(sizeof(char) * Column * Row);	// = data;

	for(int i = 0; i < Row; i++)
	{
		strcpy(*(pt + i), data[i]);
		printf("%s\n", *(pt + i));
	}

	free(pt);

	return 0;
}

