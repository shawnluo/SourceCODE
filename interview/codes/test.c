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

<<<<<<< Updated upstream
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
=======

typedef struct Data {
    int longest;
    char save[100];
} data;

/*
    slide window to find the longest uniq string
 */
data longest_uniq_sub(char *s) {
    int left = 0, right = 0;
    int len = strlen(s);
    char hash[128] = {0};
    int longest = 0;
    //char save[len + 1];
    data res;

    res.longest = 0;
>>>>>>> Stashed changes

    while(right < len) {
        ++hash[s[right]];

        while(hash[s[right]] > 1) {
<<<<<<< Updated upstream
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
=======
            --hash[s[left]];        //left move 1 step to right
            ++left;
        }

        int cur_len = right - left + 1;
        if(cur_len > res.longest) {
            res.longest = cur_len;
            strncpy(res.save, s + left, cur_len);
            res.save[cur_len] = '\0';
        }
        ++right;
    }

    return res;
>>>>>>> Stashed changes
}

data longest_palind_sub(char *s) {
    int len = strlen(s);
    int left = 0;
    int right = len - 1;
    int L = 0, R;

    data res;
    res.longest = 0;

    while(left < len) {         //left not reach to the end
        right = len - 1;
        while(left < right) {   //before right reach to left
            //find the first character from right equal to left
            while(left < right && s[left] != s[right]) {
                --right;
            }

            if(left < right) {          //not reach to left
                L = left, R = right;    //save left and right
                while(L < R && s[L] == s[R]) {  //if match
                    ++L, --R;
                }
                if(L >= R) {        //is palindar
                    //cmp and save
                    int cur_len = right - left + 1;
                    if(cur_len > res.longest) {
                        res.longest = cur_len;
                        strncpy(res.save, s + left, cur_len);
                        res.save[cur_len] = '\0';
                    }
                    break; 
                }
            }
            --right;
        }
        ++left;
    }

<<<<<<< Updated upstream
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

=======
    return res;
}

int main(void) {
    char *str = "xatydbeaaebcdeab";
>>>>>>> Stashed changes
    //int len = strlen(str);
    //int res = isPalind(str, 0, len - 1);
    //printf("%d\n", res);

    //char *s = longest_palind_sub(str);
    //printf("longest: %s\n", s);
<<<<<<< Updated upstream

    int res = longest_uniq_sub(str);
    printf("longest: %d\n", res);
=======

    data val = longest_uniq_sub(str);
    printf("val: %d\n", val.longest);
    printf("val: %s\n", val.save);

    val = longest_palind_sub(str);
    printf("val: %d\n", val.longest);
    printf("val: %s\n", val.save);
>>>>>>> Stashed changes

    return 0;
}