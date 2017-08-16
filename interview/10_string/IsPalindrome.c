
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
char *IsPalindrome(char const *str)
{
	char *Flag_Yes = "yes!";
	char *Flag_No = "NO";
    assert(str);

    int Len = strlen(str), j = Len - 1, i = 0;
    int Cent = (Len + 1) / 2;

#ifdef way1
    while (Cent--)
    {
        printf("*(str + %d)= %c\t*(str + %d) = %c\n", i, *(str + i), j, *(str + j));

        if (*(str + i++) != *(str + j--))
        {
            return Flag_No;
        }
    }
#endif

#ifdef way2
    while (Cent--)
    {
        printf("str[%d]= %c\tstr[%d] = %c\n", i, str[i], j, str[j]);

        if (str[i++] != str[j--])
        {
            return Flag_No;
        }
    }
#endif

    return Flag_Yes;
}

int main(void)
{
    char const *str = "shdwdhs";    //"show me the money!";

	char *p = IsPalindrome(str);

    printf("%s\n", p);

    return 0;
}
