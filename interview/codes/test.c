
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
        1.5 write a method to replace all spaces in a string with '%20'
            "a bc"    -   "a%20bc"
*/


/*
    1. go through str, to calculate how many space, num.
    2. inilize a new str_new, size set to (3 - 1) * num + strlen(str)
    3. 2 while loop to copy str to str_new start from tail,
        1). one from str tail, decrease
        2). another from str_new, decrease
        3). if meet space, 
            a. str--
            b. str_new[i] = '0'
            c. str_new[i - 1] = '2'
            d. str_new[i - 2] = '%'
*/
int replace_space(char *str)
{
    if(!str)
    {
        printf("str is empty!\n");
        return -1;
    }

    int len_str = strlen(str);

    int num = 0;    // how many old_ch
    char *p = str;
    while(*p)
    {
        if(*p == ' ')
        {
            num++;
        }
        p++;
    }
    //return num;

    int len_new = len_str + num * (3 - 1); // len "%20" - len ' '
    char str_new[len_new];

    char *p1 = str + len_str - 1;      // str end
    char *p2 = str_new + len_new - 1;  // new str end

    while(len_str--)
    {
        if(*str != ' ')
        {
            *p2 = *p1;
            p1--;
            p2--;
        }
        else
        {
            *p2 = '0';
            *(p2 - 1) = '2';
            *(p2 - 2) = '%';
            p1--;
            p2 -= 3;
        }
    }

    str_new[len_new] = '\0';
    printf("%s\n", str_new);
}


int main()
{
    char *str = "sh e";
    char *old_ch = " ";
    char *new_ch = "%20";
    int ret = replace_space(str);

    //printf("%d\n", ret);

    return 0;
}
