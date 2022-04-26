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

char *str = "1234561234";
/*
    slide window:
    right: to track the repeated char
    left:  to move 
*/
int longest_uniq_sub(char *s) {
    int right = 0;
    int left = 0;
    int hash[128] = {0};
    int len = strlen(s);
    int longest = 0;

    while(right < len) {
        hash[s[right]]++;

        while(hash[s[right]] > 1) {
            hash[s[left]]--;
            left++;
        }

        int cur = right - left + 1;
        longest = longest > cur ? longest : cur;

        ++right;
    }

    return longest;
}


int isPalind(char *s, int start, int end) {
    assert(s);

    //int res = 0;
    char *s1 = s + start;
    char *s2 = s + end;

    while(s1 < s2 && *s1 == *s2) {
        ++s1, --s2;
    }

    if(s1 >= s2)
        return 1;

    return 0;
}


int isPalind_ext(char *s)
{
    assert(s);
    char *s1 = s;
    char *s2 = s + strlen(s) - 1;

    while(s1 < s2 && *s1 == *s2) {
        ++s1, --s2;
    }

    if(s1 >= s2)
        return 1;

    return 0;
}


char palind_str[100] = {0};

void process_palin(char *s, int start, int end, char *palind_str) {
    //int i;
    char tmp[100];

    strncpy(tmp, s + start, end - start + 1);
    tmp[end - start + 1] = '\0';
    //printf("%s\n", tmp);

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


/*
    Longest Palindromic Substring
    1. a pointer "left" points the first char,
    2. while loop: "left" moves to the end
        loop: another pointer "right" points to the end of string
            compare s[left] and s[right], and save the bigger one to "longest"

*/
char *longest_palin_sub_ext(char *s) {
    int len = strlen(s);
    int left = 0, right = len - 1;

    while(left < len) {
        while(left < right) {
            right = len - 1;
            //ignore the not matching char
            while(left < right && s[left] != s[right]) {
                right++;
            }
            if(left < right) {
                while(left < right && s[left] == s[right])
                {
                    right++;
                }
                
            }
        }
        left++;
    }
}


int main(void) {

    //int len = strlen(str);
    //int res = isPalind(str, 0, len - 1);
    //printf("%d\n", res);

    //char *s = longest_palind_sub(str);
    //printf("longest: %s\n", s);

    int res = longest_uniq_sub(str);
    printf("longest: %d\n", res);

    return 0;
}