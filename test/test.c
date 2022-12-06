#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char *reverse_s(char *s, int start, int end) {
    int left = 0;
    int size = strlen(s);
    int right = size - 1;
    while(left < right) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
    }

    return NULL;
}


char *replace_s(char *s, int size) {
    int flag = 0;
    for(int i = 0; i < size; i++) {
        if((i > flag * 1000) && (i < 1000 * (flag + 1))) {
            reverse_s(s, flag * 1000, size - flag * 1000);
        }
    }
    return NULL;
}


//the elements in s are uniq
int isUniq(char *s, int L, int R) {
    for(int i = L; i < R - 1; i++) {
        for(int j = i + 1; j < R; j++) {
            if(s[i] == s[j]) {
                return 0;
            }
        }
    }
    return 1;
}


int long_uniq_sub(char *s) {
    int max = 0;
    int L, R;
    int size = strlen(s);
    char save[size];
    memset(save, 0, size);
    for(R = 1; R < size; R++) {
        for(L = R - 1; L >= 0; L--) {
            //if((s[L] == s[R]) && ((R - L) > max)) {
            int uniq = isUniq(s, L, R);
            //printf("L = %d, R = %d, uniq = %d, max = %d, len = %d\n", L, R, uniq, max, R - L);
            if(!uniq) {
                if(R - L > max) {
                    max = R - L;
                    strncpy(save, s + L + 1, max);
                    save[max] = '\0';
                    printf("save: %s\n", save);
                }
                break;
            }
        }

        //printf("L = %d\n", L);
        if(L == -1) {
            max = R + 1;
            strncpy(save, s, max);
            save[max] = '\0';
            //printf("%s\n", save);
        }
    }

    printf("%s\n", save);
    return max;
}


int main(int argc, char *argv[]) {
    char s[] = "abcabcdea";
    int size = strlen(s);
    //reverse_s(s, size);
    long_uniq_sub(s);

    return 0;
}