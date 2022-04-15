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
}Btree, *pBtree;

#define SIZE sizeof(Btree)

void showme(pBtree tree)
{
    if(tree == NULL)
        return;

    printf("%d ", tree->element);
    showme(tree->lchild);

    //printf("%d ", tree->rchild);
    showme(tree->rchild);
}

void createTree(Btree **T)
{
    myType data;
    scanf("%d", &data);

    if(data == -1)
    {
        *T = NULL;
    }
    else
    {
        *T = (Btree *)malloc(SIZE);
        (*T)->element = data;

        printf("left child node %d", data);
        createTree(&((*T)->lchild));

        printf("right child node %d", data);
        createTree(&((*T)->rchild));
    }
}

int main(void)
{
    pBtree tree = NULL;
    createTree(&tree);

    showme(tree);


    return 0;
}