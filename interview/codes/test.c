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


char *str = "xatydbeuaebcdeab";

char *fnd_longest_palind(char *s) {
    int i, j;
    int len = strlen(s);
//    for(i = 0; i < len; i++)

    return NULL;
}

int longest_uniq_substr_from_head(char *str) {
    int i, j;
    int len = strlen(str);

    for(i = 1; i < len; i++) {
        for(j = 0; j < i; j++) {
            if(str[i] == str[j]) {
                return i;
            }
        }
    }

    return len - 1;
}

int main(void) {
//    char *res = fnd_longest_palind(str);

    int pos = longest_uniq_substr_from_head(str);

    printf("pos = %d\n", pos);

    return 0;
}