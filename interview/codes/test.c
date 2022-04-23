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


int isPalind(char *s, int start, int end) {
    assert(s);

    int res = 0;
    char *s1 = s + start;
    char *s2 = s + end;

    while(s1 < s2 && *s1 == *s2) {
        ++s1, --s2;
    }

    if(s1 >= s2)
        return 1;

    return 0;
}


char palind_str[100] = {0};

void process_palin(char *s, int start, int end, char *palind_str) {
    int i;
    char tmp[100];

    strncpy(tmp, s + start, end - start + 1);
    tmp[end - start + 1] = '\0';
    printf("%s\n", tmp);

    if(strlen(tmp) > strlen(palind_str)) {
        strcpy(palind_str, tmp);
    }
}

char *longest_palind_sub(char *str) {
    assert(str);
    int i, j, res;
    int len = strlen(str);

    if(len == 1) return str;

    for(i = 0; i < len; i++) {
        for(j = len - 1; j > i; j--) {
            res = isPalind(str, i, j);
            if(res == 1) {   //is palinda, then compare it to palind_str[];
                process_palin(str, i, j, palind_str);
                break;
            }
        }
    }

    return palind_str;
}

#if 0
/*
    Longest Palindromic Substring


*/
char *longest_palin_sub(char *s) {
    int len = strlen(s);
}
#endif

int main(void) {
    char *str = "aacbbaca";
    //int len = strlen(str);
    //int res = isPalind(str, 0, len - 1);
    //printf("%d\n", res);

    char *s = longest_palind_sub(str);
    printf("longest: %s\n", s);


    return 0;
}