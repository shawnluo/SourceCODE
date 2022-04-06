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

int convertBfromA(int a, int b)
{
    // Absolute difference
    int moves = abs(a - b);
 
    // Print the required moves
    printf("%d\n", moves);
    return moves;
}

abcddefg  aaaddeee
#if 1
void convert(char *str)
{
    char tmp;   //save the front
    int i, j, size = strlen(str);
    int moves = 0;
    int flag = 0;
    
    for(i = 0; i < size - 1; i++)
    {
        for(j = i + 1; j < size; j++)
        {
            if(str[j] == str[i])
            {
                flag = 0;
                continue;
            }
            else    //save the tmp
            {
                if(flag == 1)
                {
                    moves += convertBfromA(str[i], str[j]);
                    flag = 0;
                }
                if(flag == 0)
                    flag = 1;
            }
        }
    }
}
#endif

int main()
{
    char A = 'd', B = 'a';
 
    convertBfromA(A, B);
 
    return 0;
}