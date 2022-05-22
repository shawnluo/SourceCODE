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

int replace_space_with(char *str) {
    int i, j, k;
    int len = strlen(str);
    int n_space = 0;

    for(i = 0; i < len; i++) {
        if(str[i] == ' ') {
            n_space++;
        }
    }

    for(i = len; i >= 0;) {
        
    }

}


int main(void) {
    char str[20] = "123 4  1516 ";

    replace_space_with(str);
    //printf("ret = %d\n", ret);
    printf("str = %s\n", str);

	return 0;
}