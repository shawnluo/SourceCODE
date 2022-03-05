#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define SIZE 10



void test()
{
    char *str = "+19";
    char *p = str;

    long val = strtol(str, &p, 10);
    printf("%ld\n", val);
    printf("%s\n", p);
}

void find_num()
{
    char *str = "ab234cid*(s349*(20kd";
    char *p = str;
    while (*p) // While there are more characters to process...
    {
        if( isdigit(*p) || ( (*p == '-' || *p == '+') && isdigit(*(p + 1))))    // Found a number
        {
            //printf();
            long val = strtol(p, &p, 10);   // Read number
            printf("%ld\n", val);           // and print it.
        } 
        else        // Otherwise, move on to the next character.
        {
            p++;
        }
    }
}

int main(void)
{
    //find_num();
    test();
}