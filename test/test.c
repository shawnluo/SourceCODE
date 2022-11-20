#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int longest_uniq_substring(char *s, char *max_s, int size) {
    int len = 0;
    int max = 0;

    for(int i = 1; i < size; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(s[i] == s[j]) {
                len = i - j;
                if(len > max) {
                    max = len;
                    strncpy(max_s, s, len);
                    max_s[j] = '\0';
                }
            }
        }
    }
    return 0;
}


int longest(char *s) {
    int size = strlen(s);
    char s1[size];
    int max = 0;
    char max_s[size];
    for(int i = 0; i < size; i++) {
        longest_uniq_substring(s + i, s1, size - i);
        if(strlen(s1) > max) {
            strcpy(max_s, s1);
        }
    }
}


int main(int argc, char *argv[]) {
    char *s = "abcabce";
    longest_uniq_subs(s);

    return 0;
}