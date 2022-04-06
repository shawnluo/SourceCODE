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
int n;   //数组元素个数
int sum; //数组中存在n个元素和为sum
int flag;

void cal_sum(int n, int sum) //求数组中是否存在一些元素和等于sum
{
    if (nums[n] == sum)
    {
        flag = 1; //假设数组的最后一个元素等于和sum，将flag变量置为true
        return ;
    }

    if (n == 0)
    {
        return; //搜索完了整个数组返回
    }
    
    // printf("%d ", nums[n]);
    cal_sum(n - 1, sum - nums[n]); //说明取了nums[n]元素
    cal_sum(n - 1, sum);           //说明没有取nums[n]
}


int main()
{
    int n = 5;
    int sum = 22;
    flag = 0; //初始时，将flag置为false，当找到某些元素和为sum的时候在cal_sum函数中flag的值将改变
    cal_sum(n, sum);
    if (flag)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}