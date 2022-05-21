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


            
             ongoing-------------------------------




*/


int lengthOfLongestSub(char *s) {
    int left = 0, right = 0;
    int len = strlen(s);
    char hash[128] = {0};
    int max = 0;

    while(right < len) {
        hash[s[right]]++;
        
        while(s[right] > 1) {
            hash[s[left]]--;
            left++;
        }

        int size = right - left + 1;
        if(max < size) {
            max = size;
        }
    }
    return left;
}


int isSub(char *s, char *sub) {
    int i, j, len;
    for(i = 0; i < strlen(s); i++) {
        int k = i;
        for(j = 0; j < strlen(sub); j++) {
            if(s[k++] != sub[j]) {
                break;
            }
        }

        printf("j = %d\n", j);
        if(j == strlen(sub)) {
            return 1;
        }        
    }
    return 0;
}


//string copy
char *myStrcpy(char *des, const char *src) {
    assert(src);
    char *res = des;
    while(*des = *src) {
        des++;
        src++;
    }
    return res;
}


int main() {
    char *str = "abcdefabce1234";
    char *sub = "1234";
    //int val = isSub(str, sub);
    //printf("%d\n", val);

    char des[100] = {0};
    char *s = myStrcpy(des, str);
    printf("%s\n", s);
	return 0;
}