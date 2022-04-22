#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>


/*
    slide window:
    right: to track the repeated char
    left:  to move 
*/
int longest_uniq_sub(char *s) {
    int left = 0;
    int right = 0;
    int res = 0;
    int len = strlen(s);
    char hash[128] = {0};
    
    while(right < len) {
        hash[s[right]]++;

        while(hash[s[right]] > 1) {
            hash[s[left]]--;
            left++;                     //beautiful.
        }
        int len_uniq = right - left + 1;
        res = res > len_uniq ? res : len_uniq;
        right++;
    }
    return res;
}

int main(void) {
    char *str = "a3456bc3abcde1abcdefgh";
    int val = longest_uniq_sub(str);

    printf("%d\n", val);

    return 0;
}