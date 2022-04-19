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

char **process_logs(char **str, int len, int threshold)
{
	char *p = NULL;
	
}

int main()
{
    char *str[] = {"1 2 100", "2 3 100", "4 4 290", "19 2 600"};
    int len = 4;
    int threshold = 7;
    process_logs(str, len, threshold);

	return 0;
}