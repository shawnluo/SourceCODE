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

/*
Design  an  algorithm  and  write  code  to  remove  the  duplicate  
characters  in  a  string without using any additional buffer  
NOTE: One or two additional variables are fineAn extra copy of the array is not
*/

//way1. maintain a string without duplicate
void remove_dup(char *str) {
    int i, j;
    int len = strlen(str);
    int k = 0;  //without dup

    //k = 1;
    for(i = 1; i < len; i++) {
        for(j = 0; j <= k; j++) {
            if(str[i] == str[j]) {
                break;
            }
        }
        if(j > k) {
            str[++k] = str[i];
        }
    }
    str[++k] = '\0';
}

/*way2. go through the string from left to right, 
if space then move all the right chars to left
*/


int main() {
    char str[20] = "1234156";

    remove_dup(str);
    printf("str = %s\n", str);

	return 0;
}