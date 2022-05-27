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



#if 0
void print_bits(int data) {
    char *p = (char *)&data + 3;

    for(int i = 0; i < 4; i++) {
        for(int j = 7; j >= 0; j--) {
            int tmp = (*p) & (1 << j);
            if(tmp) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf(" ");

        p--;
    }
}

int fibo(int n) {
    if(n <= 2) {
        return n;
    } else {
        return fibo(n - 1) + fibo(n - 2);
    }
}

int reverse(int x) {
    int res = 0;
    while(x != 0) {
        res = res * 10 + x % 10;
        x = x / 10;
    }
    return res;
}


#endif


int reverse(int n) {
    int res = 0;
    while(n) {
        res = res * 10 + n % 10;
        n /= 10;
    }

    return res;
}


#define REG_DEV (*(volitle unsigned int *)0x80004000)


int main(void) {
    int ret = reverse(51);
    printf("%d\n", ret);
	return 0;
}