#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

void process_log(char **s, int len, int threshold)
{
    int i;
}

int main(void)
{
    char *str[] = {"1 2 100", "2 3 100", "4 4 290", "19 2 600"};
    int len = 4;
    int threshold = 7;
    process_log(str, len, threshold);

    //printf("%s\n", str[0]);
    return 0;
}