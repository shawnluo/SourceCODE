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
    int len = strlen(s);
    int left = 0;
    int right = 0;

    char hash[128] = {0};
    int res = 0;
    while(right < len) {
        hash[s[right]]++;

        while(hash[s[right]] > 1) { //if the char repeat - hash > 1
            hash[s[left]]--;
            left++;                 //alway will find the repeat left char
        }

        res = res > (right - left + 1) ? res : (right - left + 1);
        right++;
    }
    return res;
}


#if 0
int lengthOfLongestSub_2(char *s) {
    int left = 0, right = 0;
    int len = strlen(s);

    char hash[128] = {0};
    int res = 0;
    while(right < len) {
        hash[s[right]]++;

        while(hash[s[right]] > 1) {
            hash[s[left]]--;
            left++;
        }

        int dy_len = right - left + 1;  //the length of non repeat string
        
        if(res > dy_len) {
            dy_len = res;
            strncpy(max_s, s + , 
        }
            
        right++;
    }

    return res;
}
#endif


int main() {
    char *str = "abcdefabce1234";
    int val = lengthOfLongestSub(str);
    printf("%d\n", val);

	return 0;
}