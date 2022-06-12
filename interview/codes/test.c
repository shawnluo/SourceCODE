#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>

<<<<<<< HEAD

int main(void) {
    int ret = reverse(51);
    printf("%d\n", ret);
=======




int main(void) {
    char *s1[] = {"abc", "good"};
    //char (*s2)[] = {"123", "4567"};

    char *p = s1[0];

    printf("%s\n", p);
    printf("%s\n", p + 1);

>>>>>>> test rebase
	return 0;
}