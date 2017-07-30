#include <stdio.h>
#include <stdlib.h>


char *ss()
{
	int i = 0;
	char *str[] = { "good", "day", "to", "die", "!" };
    char *yy[5];

	for(i = 0; i < 5; i++)
	{
		yy[i] = str[i];
		printf("%p\t", yy[i]);
	}
	printf("\n");
	
    return yy[0];
//    return yy;
}

int main()
{
    char *str = ss();

    printf("%s\n", str);

    return(0);
}
