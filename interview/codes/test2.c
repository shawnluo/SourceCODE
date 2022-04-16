#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
#include <time.h>
#include <unistd.h>
#include <assert.h>

typedef struct treeNode
{
    int element;
    struct treeNode *lchild;
    struct treeNode *rchild;
}Btree, *pBtree;

#define SIZE sizeof(Btree)

int arr[] = {0, 1, 2, -1, -1, 3, -1, -1, 4, 5, -1, -1, 6, -1, -1};
int len = sizeof(arr) / sizeof(arr[0]);

void showme_C_L_R(pBtree tree)
{
    if(tree == NULL)    return;

    printf("%d ", tree->element);
    showme_C_L_R(tree->lchild);
    showme_C_L_R(tree->rchild);
}

void showme_L_C_R(pBtree tree)
{
    if(tree == NULL)    return;

    showme_L_C_R(tree->lchild);
    printf("%d ", tree->element);
    showme_L_C_R(tree->rchild);
}

void showme_L_R_C(pBtree tree)
{
    if(tree == NULL)    return;

    showme_L_R_C(tree->lchild);
    showme_L_R_C(tree->rchild);
    printf("%d ", tree->element);
}

void createTree(Btree **T)
{
    int data;
    static int i = 0;
    data = arr[i++];
    //scanf("%d", &data);

    if(data == -1)  *T = NULL;
    else
    {
        *T = (Btree *)malloc(SIZE);
        (*T)->element = data;

        //printf("left child node: ");
        createTree(&((*T)->lchild));

        //printf("right child node: ");
        createTree(&((*T)->rchild));
    }
}

pBtree invert_bt(pBtree tree)
{
    if(tree == NULL)
    {
        return NULL;
    }
    
    pBtree tmp = (tree)->lchild;
    (tree)->lchild = invert_bt((tree)->rchild);
    tree->rchild = invert_bt(tmp);
    return tree;
}


int main(void)
{
    pBtree tree = NULL;
    createTree(&tree);

    printf("C_L_R: ");
    showme_C_L_R(tree);
    printf("\n");

    printf("L_C_R: ");
    showme_L_C_R(tree);
    printf("\n");

    printf("L_R_C: ");
    showme_L_R_C(tree);
    printf("\n");

    tree = invert_bt(tree);
    showme_L_C_R(tree);
    printf("\n");
=======
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


int main(void)
{
    int i, *pa, a[] = {1, 2, 3, 4, 5};

    pa = a;

    for(i = 0; i <= 9; i++)
    {
        printf("%d\n", *pa);
        pa++;
    }
>>>>>>> e42e19d3858d3492941967761b364574a2100dc3

    return 0;
}