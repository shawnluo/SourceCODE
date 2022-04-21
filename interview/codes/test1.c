#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>


void test(char *str, char *s1)
{
    strcpy(s1, "gooday");
    //return s1;
}


int main()
{
    char *p = "";
    printf("%ld\n", strlen(p));

    p = "gd";
    printf("%ld\n", strlen(p));

    char *s = (char *)malloc(100);
    //test(p, s);
    //printf("%s\n", s);
    printf("%ld\n", strlen(s));
	return 0;
}