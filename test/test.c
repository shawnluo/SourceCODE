#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
    step 1: if it hasn't repeat character
        a b c d a
    step 2: if it has uniq characters, then find the longest.
        a b c d a b c d e f
*/

int Has_unqi_char(char *str) {
    int size = strlen(str);
    if(size == 1) {
        return 1;
    }

    for(int i = 1; i < size; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(str[i] == str[j]) {
                return 0;
            }
        }
    }

    return 1;
}


int has_uniq_char(char *s) {
    assert(s);
    int size = strlen(s);
    if(size == 1) {
        return 1;
    }

    //a b c d
    for(int i = 0; i < size - 1; i++) {
        for(int j = i + 1; j < size; j++) {
            if(s[i] == s[j]) {
                return 0;
            }
        }
    }
    return 1;
}

//a b c d
char *longest_sub(char *s) {
    int size = strlen(s);
    //go throught every substring
    for(int i = 0; i < size - 1; i++) {
        for(int j = i + 1; j < size; j++)
    }
}


char *longest_uniq_subs(char *str) {
    int size = strlen(str);
    char cur_str[size];
    int max_len = 0;
    int cur_len = 0;
    char max_str[size];
    for(int i = 0; i < size - 1; i++) {
        for(int j = i + 1; j < size; j++) {
            strncpy(cur_str, str + i, j - i);
            if(Has_unqi_char(cur_str)) {
                cur_len++;
            } else {
                if(cur_len > max_len) {
                    max_len = cur_len;
                    strncpy(max_str, cur_str + i, cur_len);
                    max_str[cur_len] = '\0';
                    memset(cur_str, 0, size);
                    cur_len = 0;
                } else {
                    cur_len = 0;
                    memset(cur_str, 0, size);
                }
            }        
        }
    }
    printf("%s\n", max_str);
    return NULL;
}


int new_arr[100];

int *sort_square(int *arr, int size) {
    if(size <= 0) {
        return -1;
    }

    if(size == 1) {
        return arr;
    }
    if(all_element(arr, size) >= 0) {
        return arr;
    } else if(all_element(arr, size) <= 0) {
        return reverse_arr(arr, size);
    }

    //static int new_arr[size];
    int p1 = 0;
    int p2 = size - 1;
    while(arr[p1] <= 0 || arr[p2] >= 0) {
        if(arr[p1] <= 0 && arr[p2] >= 0) {
            if(sqrt(arr[p1]) >= sqrt(arr[p2])) {
                new_arr[size - 1] = sqrt(arr[p1]);
                p1++;
            } else {
                new_arr[size - 1] = sqrt(arr[p2]);
                p2--;
            }
        } else {
            if(arr[p2] < 0) {
                new_arr[size - 1] = arr[p1];
                p1++;
            } else {
                new_arr[size - 1] = arr[p2];
                p2--;
            }
        }
        size--;
    }
    return new_arr;
}


int main(int argc, int *argv[]) {
    #if 1
    char *str = "abcabce";
    longest_uniq_subs(str);
    #else
    char *str = "abcde";
    char newStr[10] = "xxxxxx";

    //newStr[0] = str[0];
    //newStr[1] = str[1];
    //newStr[2] = '\0';

    strncpy(newStr, str + 1, 3);
    newStr[3] = '\0';

    printf("%s\n", newStr);
    #endif

    return 0;
}