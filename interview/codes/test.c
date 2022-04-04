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



typedef int myType;
typedef struct treeNode
{
    myType element;
    struct treeNode *lchild;
    struct treeNode *rchild;
}Btree;

#define SIZE sizeof(Btree)

void createTree(Btree **T)
{
    myType data;
    scanf("%d", &data);

    if(data == - 1)
    {
        *T = NULL;
    }
    else
    {
        *T = (Btree *)malloc(SIZE);
        (*T)->element = data;
        printf("left child node %d", data);
        
    }
}

int main(void)
{
    printf("%d\n", );

    return 0;
}