
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "color.h"



char *mystrcpy(char *des, const char *src)
{
    assert(des && src);

	char *address = des;
	while((*des++ = *src++) != '\0')	//string des copied the '\0' of src
	{
		;
	}
	
    return address;
}



int main(void)
{
	char strSrc[] = "gooddd";
	printf("Len = %d\n", (int)strlen(strSrc));
	char *strNew = (char *)malloc(strlen(strSrc + 1));	//strlen will not count '\0'

	char *p_strNew = mystrcpy(strNew, strSrc);
	printf("strNew = %s\n", p_strNew);

    return 0;
}

