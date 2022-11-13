#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int longest_no_repeat_subs(char *str) {
    int i, j;
    int hash[256] = {0};
    int len = strlen(str);
    int current_len = 0;
    int max = 0;
    int tx = 0;
    char longest_str[100] = {0};

    for(i = 0; i < len; i++) {
        for(j = i; i < len; j++) {
            if(hash[str[j]] == 0) {
                hash[str[j]] = 1;
                current_len++;
            } else {
                memset(hash, 0, sizeof(hash));
                current_len = j - i + 1;
                if(current_len > max) {
                    max = current_len;
                    for(int x = i, tx = 0; x < j; x++, tx++) {
                        longest_str[tx] = str[x];
                    }
                    longest_str[tx] = '\0';
                }
                break;
            }
        }
    }
}


void longest_sub(char *str) {
    int hash[256] = {0};
    int len = strlen(str);
    int max = 0;
    int longest_len = 0;
    char save[200] = {0};

    for(int i  = 0; i < len; i++) {

    }
}


#if 0
int main(void) {
    char str[100] = "Show me the money!";
    char *p = str;
    int len = strlen(str);
    if(!p) {
        printf("empty string!\n");
        return -1;
    }

    p = str;
    int count = 0;

    while(*p != '\0') {
        if(*p == ' ') {
            count++;
        }
        p++;
    }
    printf("%d\n", count + 1);

    return 0;
}
#endif