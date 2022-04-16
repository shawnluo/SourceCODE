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

typedef void (*FunP)(int);

void MyFun(int x)
{
	printf("%d\n", x);
}

int main()
{
	FunP fun;
	fun = MyFun;
	fun(10);

	return 0;
}