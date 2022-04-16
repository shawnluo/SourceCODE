#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


/*
    ""
*/
void extract_str(char **s, int len)
{
    char *p[100];
    p = s;

}

int main(void)
{
    char *str[] = {"1 2 100", "2 3 100"};
    int len = 2;
    extract_str(str, len);
    return 0;
}