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


//pass string pointer array, and print 
void show_str_arr() {
    
}

int main(void) {
    char *s1[] = {"abc", "1234", "defghi"};
    char *p = s1[0];

    printf("%s\n", s1);

	return 0;
}