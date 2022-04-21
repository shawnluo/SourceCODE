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


typedef void (*func)(char **arr, int row, int threhold);

typedef struct LOG{
	int data;
	int times;
}log;

void test(char **arr, int row, int threhold)
{
	int i, j = 0;
	int k = 0;
	char tmp1[100], tmp2[100];
	int data[100] = {0};

	log myLog[100] = {0, 0};

	for(i = 0; i < row; i++)
	{
		j = 0;
		char *p = arr[i];

		while(*p != ' ')
		{

			tmp1[j++] = *p++;
		}
		tmp1[j++] = '\0';
		p++;

		j = 0;
		while(*p != ' ')
		{
			tmp2[j++] = *p++;
		}
		tmp2[j++] = '\0';

		if(atoi(tmp1) == atoi(tmp2))
		{
			data[k++] = atoi(tmp1);
		}
		else
		{
			data[k++] = atoi(tmp1);
			data[k++] = atoi(tmp2);
		}
	}

	for(i = 0; i < k; i++)
	{
		printf("%d, ", data[i]);
	}
	printf("\n");

	//get the list
	int index = 1;
	myLog[0].data = data[0];

	for(i = 1; i < k; i++)
	{
		for(j = 0; j < index; j++)
		{
			if(myLog[j].data == data[i])
				break;
		}
		if(j == index)
		{
			myLog[index++].data = data[i];
		}
	}

	for(i = 0; i < k; i++)
	{
		for(j = 0; j < index; j++)
		{
			if(myLog[j].data == data[i])
			{
				myLog[j].times++;
			}
		}
	}

	for(i = 0; i < index; i++)
	{
		if(myLog[i].times >= threhold)
			printf("%d - %d\n", myLog[i].data, myLog[i].times);
	}
}


int main()
{
	char *arr[] = {"0 1 2", "4 5 6", "1 2 7", "0 1 100"};
	int col = sizeof(arr[0]);
	int row = sizeof(arr) / (sizeof(char) * col);
	int threhold = 2;
/*
	printf("col: %d\n", col);
	printf("%d\n", (int)sizeof(arr));
	printf("row: %d\n", row);
*/

	func MyFun;
	MyFun = test;

	MyFun(arr, row, threhold);

	return 0;
}