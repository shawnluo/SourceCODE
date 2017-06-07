#include <stdio.h>
#include <stdlib.h>

#define true 1
char** my_split(char * str, char sym)
{
    if (!str || !*str) return 0;
    const int ini = 10;
    int size = ini;
    char ** str_table = (char **)malloc(sizeof(char*) * size);
    int line = 0;
    while (true)
    {
        if (line >= size - 1)
        {
            size *= 2;
            str_table = (char **)realloc(str_table, sizeof(char*) * size);
        }
        str_table[line++] = str;
        while (*str && *str != sym)
        {
            str++;
        }
        if (!*str)
        {
            break;
        }
        else
        {
            *str = '\0';
            while (*++str == sym);
        }
    }
    str_table[line] = 0;
    return str_table;
}

int main()
{
	int i;
    char str[] = {"sss ddkid ddafad  diuyd"};

    char ** str_table = my_split(str, ' ');

    if (str_table)
    {
        for (i = 0; str_table[i]; i++)
        {
            puts(str_table[i]);
        }
    }
    free(str_table);
    return 0;
}