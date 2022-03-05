
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


void string2num()
{
#ifdef way1
    char *str = "1234";
    int arr[] = {0};
    int val = atoi(str);
#endif

#ifdef way2
    char *str = "1234";
    int val;
    sscanf(str, "%d", &val);
#endif

#ifdef way3
    char *str = "1234ABC";
    char *ptr = NULL;               //point to where the number stops, it's "ABC"
    int val = strtol(str, &ptr, 10);
#endif

#ifdef way4     //one by one to parse
    char c = 'A';
    int x;
    x = c - 0x40;
#endif

}



int main(void)
{
    string2num();

    return 0;
}