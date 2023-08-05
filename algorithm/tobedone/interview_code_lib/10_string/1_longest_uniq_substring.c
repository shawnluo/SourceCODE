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


//longest uniq substring



typedef struct DATA{
    int pos;
    int size;
    char str[100];
} data;

//way1. brutal force
int longest_uniq_substr_from_head(char *str) {
    int i, j;
    int len = strlen(str);

    for(i = 1; i < len; i++) {
        for(j = 0; j < i; j++) {
            if(str[i] == str[j]) {
                return i;
            }
        }
    }

    return len - 1;
}

int BF_longest_uniq_sub(char *str) {
    int i;
        int pos;
    int len = strlen(str);
    char *p = NULL;
    int longest = 0;

    for(p = str; p < str + len; p++) {
        pos = longest_uniq_substr_from_head(p);
        if(pos > longest) {
            longest = pos;
        }
    }
    return longest;
}


/*
    way2: slide window
    use left and right to indicate the repeated char
    use hash to record the repeat status.
    when hash[right] > 1, then move left towards right, and decrease hash[left]
    until hash[right] == 1, then left is the repeat char left side.
*/
data SW_longest_uniq_sub(char *str) {
    int left = 0;
    int right = 0;
    int len = strlen(str);
    char hash[128] = {0};
    //int longest = 0;
    data longest_str;

    longest_str.pos = 0;
    longest_str.size = 0;
    memset(longest_str.str, 0, 100);

    while(right < len) {
        hash[str[right]]++;

        while(hash[str[right]] > 1) {
            hash[str[left]]--;
            left++;
        }
        int size = right - left + 1;
        if(size > longest_str.size) {
            longest_str.pos = left;
            longest_str.size = size;
            memset(longest_str.str, 0, 100);
            strncpy(longest_str.str, str + left, size);
        }

        right++;
    }

    return longest_str;
}

int main(void) {
    char *str = "aabca";

    int longest = BF_longest_uniq_sub(str);
    printf("longest = %d\n", longest);

/*
    data longest;
    longest = SW_longest_uniq_sub(str);
    printf("pos = %d\n", longest.pos);
    printf("size = %d\n", longest.size);
    printf("str = %s\n", longest.str);
*/
    return 0;
}