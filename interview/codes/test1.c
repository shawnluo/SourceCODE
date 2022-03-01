#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define SIZE 10

#if 1
int main(void)
{
    int **pArr = NULL;

    pArr = (int **)malloc(sizeof(int *) * SIZE);
    memset(pArr, 0, sizeof(int *) * SIZE);
    
    int index = 0;
    pArr[index] = (int *)malloc(sizeof(int) * SIZE);
    memset(pArr[index], 0, sizeof(int) * SIZE);

    for(int i = 0; i < SIZE; i++)
    {
        pArr[index][i] = i;
    }

    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", pArr[index][i]);
    }
    printf("\n");

    free(pArr[index]);
    free(pArr);

    return 0;
}

#else

int main(void)
{
    int (*pArr)[SIZE] = NULL;

    pArr = (int *)malloc(sizeof(int) * SIZE);
    
    for(int i = 0; i < SIZE; i++)
    {
        (*pArr)[i] = i;
    }

    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", (*pArr)[i]);
    }
    printf("\n");

    int (*pTmp)[SIZE] = pArr;

    pArr++;
    pArr = (int *)malloc(sizeof(int) * SIZE);
    
    for(int i = 0; i < SIZE; i++)
    {
        (*pArr)[i] = i * 10;
    }

    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", (*pArr)[i]);
    }
    printf("\n");

    free(pTmp);
    free(pArr);

    return 0;
}

#endif