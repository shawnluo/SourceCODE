#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int is_uniq(char *s, int size) {
    for(int i = 0; i < size - 1; i++) {
        if(s[size] == s[i]) {
            return 0;
        }
    }
    return 1;
}


void longest(char *s) {
    int start, end;
    int size = strlen(s);
    int max = 0;
    char s_max[size];

    start = 0;
    end = 1;
    memset(s_max, 0, size);
    while(end < size) {
        while((end < size) && is_uniq(s + start, end - start)) {
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


int main(int argc, char *argv[]) {
    char *s = "abcacbe";
    longest(s);

    return 0;
}