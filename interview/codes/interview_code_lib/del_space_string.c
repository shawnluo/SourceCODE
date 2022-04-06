
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>



void del_space()
{
    char str[200] = "sh ow me !";
    int size = strlen(str);
    int n = size;

    for(int i = 0; i < size; i++)
    {
        //printf("   %c\n", str[i]);
        if(str[i] != ' ')
        {
            str[n] = str[i];
            n++;
        }
    }
    str[n] = '\0';
    //printf("%s\n", str);
    strcpy(str, str + size);
    printf("%s\n", str);
}

void del_space_2()
{
    char str[200] = "sh ow me  !";
    int size = strlen(str);
    //int space = 0;
    int newSize = size;

    printf("%s\n", str);

    while((size - 1) >= 0)
    {
        if(str[size - 1] != ' ')
        {
            str[newSize - 1] = str[size - 1];
            size--;
            newSize--;
        }
        else
        {
            size--;
        }
    }

    printf("%s\n", str);
}



void del_spaces_3()
{
    char str[] = "sh    o m   e! ";
    char *p = str;
    char *q = str;

    while(*p != '\0')
    {
        if(*p == ' ')
        {
            q = p;

            while(*q != '\0')
            {
                *q = *(q + 1);
                q++;
            }
            *q = '\0';
            p--;
        }
        p++;
    }

    printf("%s\n", str);
}


int main(void)
{
    del_space_2();
    del_spaces_3();

    return 0;
}