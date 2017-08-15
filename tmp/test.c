
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include <stdbool.h>
#include "color.h"


void print_trace()
{
    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}

#define way1
char *IsPalindrome(char const *str, char *Flag)
{
    assert(str && Flag);

    int Len = strlen(str), j = Len - 1, i = 0;
    int Cent = (Len + 1) / 2;

#ifdef way1
    while (Cent--)
    {
        printf("*(str + %d)= %c\t*(str + %d) = %c\n", i, *(str + i), j, *(str + j));

        if (*(str + i++) != *(str + j--))
        {
            strcpy(Flag, "no!");
            return Flag;
        }
    }
    strcpy(Flag, "yes!");
#endif

#ifdef way2
    while (Cent--)
    {
        printf("str[%d]= %c\tstr[%d] = %c\n", i, str[i], j, str[j]);

        if (str[i++] != str[j--])
        {
            strcpy(Flag, "no!");
            return Flag;
        }
    }

    strcpy(Flag, "yes!");
#endif

    return Flag;
}


long fib(int num)
{
	long i, t_1 = 0, tmp = 0, t = 0;
	
	for(i = 0; i < num; i++)
	{
		if(i == 0)
		{
			t_1 = 0;
			t = 0;
			continue;
		}
		
		if(i == 1)
		{
			t_1 = 0;
			t = 1;
			continue;
		}
		tmp = t;		//tmp = 1				2
		t = t + t_1;		//t1 = 1	t = 1 + 1	1 2 + 1
		t_1 = tmp;		//t1 = 1				1
	}

	return t;
}

long factorial(int n)
{
	long result;
	
	if(n == 0 || n == 1)
	{
		result = 1;
	}
	else
	{
		result = factorial(n - 1) + factorial(n - 2);
	}

	return result;
}

int main(void)
{
//	long x =	fib(8);
	long x = factorial(8);

	printf("x = %ld\n", x);
	
	return 0;
}
