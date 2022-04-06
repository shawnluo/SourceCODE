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

int nums[6] = {1, 2, 3, 4, 5, 6};
int n; //数组元素个数
int m; //数组中存在n个元素和为m
int flag;

void sum(int n, int m) //求数组中是否存在一些元素和等于m
{
    if (nums[n] == m)
        flag = 1; //假设数组的最后一个元素等于和m，将flag变量置为true
    else if (n == 0)
        return; //搜索完了整个数组返回
    else
    {
        sum(n - 1, m - nums[n]); //说明取了nums[n]元素
        sum(n - 1, m);           //说明没有取nums[n]
    }
}

int main()
{
    int n = 5;
    int m = 12;
    flag = 0; //初始时，将flag置为false，当找到某些元素和为m的时候在sum函数中flag的值将改变
    sum(n, m);
    if (flag)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}