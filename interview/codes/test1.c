#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int cmp_string(const char *a, const char *b)
{
    assert(a);
    assert(b);
    assert(1 > 0);

    int size_a = strlen(a);
    int size_b = strlen(b);

    while((*a++ == *b++) && size_a != 0 && size_b != 0)
    {
        size_a--;
        size_b--;
    }

    if((size_a == 0) && (size_b == 0))
    {
        printf(" - 111\n");
        return 0;
    }
    else if(size_a == 0)
    {
        printf(" - 222\n");
        return -1;
    }
    else if(size_b == 0)
    {
        printf(" - 333\n");
        return 1;
    }
    else
    {
        printf(" - 444\n");
        return *a > *b ? 1 : -1;
    }

    return 0;
}

void show(char *str, char *str2)
{
    //str = str2;
    strcpy(str, str2);
    printf("%s\n", str);
}

int main(void)
{
    char str[10] = "show";
    char str2[10] = "me";
    show(str, str2);

    printf("2 - %s\n", str);
    //for(int i = 0; i < sizeof(str2); i++)
    //printf("%c\t", str2[i]);
    //printf("\n");
    //printf("%d\n", strcmp("abcd", "abc"));
    return 0;
}