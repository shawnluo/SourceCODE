#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *longest_uniq_subs(char *str) {
    int size = strlen(str);

    for(int i = 0; i < size - 1; i++) {
        for(int j = i + 1; j < size; j++) {
            
        }
    }
}

int main(int argc, int *argv[]) {
    #if 0
    test();
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