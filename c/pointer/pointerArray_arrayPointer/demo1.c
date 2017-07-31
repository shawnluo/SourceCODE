#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LEN 20
typedef char* PCHAR;



#if 0
char *ss()
{
    int  i      = 0;
    char *str[] = { "good", "day", "to", "die", "!" };
    char *yy[5];

    int  intt[5] = { 1, 2, 3, 4, 5 };
    int  aaa[5];

    memcpy(aaa, intt, sizeof(aaa));

    for (i = 0; i < 5; i++)
    {
        printf("%d\t", aaa[i]);
    }
    printf("\n");

//	char **p[5] =
    for (i = 0; i < 5; i++)
    {
        yy[i] = str[i];
        printf("%p\t", yy[i]);
    }
    printf("\n");

    return yy[0];
//    return yy;
}
#endif

#if 1
void showme(char *p[])
{
    int i = 0;

    for (i = 0; i < 5; i++)
    {
        printf("%s\t", p[i]);
    }
    printf("\n");
}

char **fun(char *pArray[])
{
	int i;
	PCHAR angry[] = { "are", "you", "crazy", "?", "!" };

	for(i = 0; i < 5; i++)
	{
		strcpy(pArray[i], angry[i]);
	}
	showme(pArray);
	
    return pArray;
}


int main()
{
	int i;
	PCHAR word[5]= { "good", "day", "to", "die", "!" };
    PCHAR array[5];

	for(i = 0; i < 5; i++)
	{
		array[i] = (char *)malloc(LEN);
		memset(array[i], '\0', LEN);
		strcpy(array[i], word[i]);
	}
	showme(array);

    char **p = fun(array);
    showme(p);

    return(0);
}
#endif

#if 0
int **your_function(int *pArray[])
{
    int i = 1;

    *pArray[0] = 1;
    *pArray[1] = 2;
    *pArray[2] = 3;
    return pArray;
}

void print_array(int *pArray[])
{
    int i = 0;

    for ( ; i < 3; i++)
    {
        printf("%d ", *pArray[i]);
    }
    printf("\n");
}

void main()
{
    int a = 5, b = 4, c = 3;
    int *array[3] = { &a, &b, &c };
    int **p;

    print_array(array);
    p = your_function(array);
    print_array(p);
}
#endif
