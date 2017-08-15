
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

int main(void)
{
    char *str = "shdwdhs";    //"show me the money!";
    char *Flag = (char *)malloc(10);

    printf("%s\n", IsPalindrome(str, Flag));

    return 0;
}
