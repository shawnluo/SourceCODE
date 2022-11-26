#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//solution1
// compare s[size] with s[0, size)
int cmp_end(char *s, int size) {
    for(int i = 0; i < size - 1; i++) {
        if(s[size] == s[i]) {
            return 0;
        }
    }
    return 1;
}

/*  using slide window
    maintain a array[start, end] is uniq, 
        if it's uniq,       then end++
        if it's not uniq,   then start++
*/
void longest(char *s) {
    int start, end;
    int size = strlen(s);
    int max = 0;
    char s_max[size];

    start = 0;
    end = 1;
    memset(s_max, 0, size);
    while(end < size) {
        while((end < size) && cmp_end(s + start, end - start)) {
            end++;
        }
        if((end < size) && (end - start > max)) {
            max = end - start;
            strncpy(s_max, s + start, end - start);
            s_max[end - start] = '\0';
        } else if((end == size) && (end - start + 1 > max)) {
            max = end - start + 1;
            strncpy(s_max, s + start, end - start + 1);
            s_max[end - start + 1] = '\0';
        }
        start++;
    }
    printf("%s\n", s_max);
}


/*solution2:
using hash table
*/
int hash[100] = {0};
int is_uniq(char *s, int start, int end) {
    int size = strlen(s);
    for(int i = 0; i < size; i++) {
        if(hash[s[]])
    }
}

//using hash table
void longest_1(char *s) {
    int size = strlen(s);
    int start = 0;
    int end = 0
    int max = 0;
    char s_max[size];

    for(int i = 0; i < size; i++) {
        for(int j = 1; j < size; j++) {
            if(is_uniq(s, start, end)) {
                max = end - start;
            }
        }
    }
}


int main(int argc, char *argv[]) {
    char *s = "abcacbe";
    longest(s);

    return 0;
}