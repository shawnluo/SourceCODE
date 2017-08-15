
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "color.h"



#define Row       5
#define Column    7

int main(void)
{
/**************data[N][m]******************************************
 *	the end of string will follow with '\0'
 *****************************************************************/
    char *data[Row] = { "123456", "7890pK", "Shaw", "Alex", "Joe" };
    //============END=================================


/*============usage of char *str[N]=================================
 *			char str[N][]	
 *	1. str is a array, has N elements, every element is a pointer!
 *	2. m is the second dimension of this 2 dimensions array!
 *	3. free every name[i]
 ********************************************************************/
    char *name[Row] = { NULL };

    /******malloc way1:*****************************************************
     *      malloc for every name[i]
     ********************************/
    for (int i = 0; i < Row; i++)
    {
        name[i] = (char *)malloc(sizeof(char) * Column);
        strcpy(name[i], data[i]);
        my_trace(BRIGHT, GREEN, BLACK, "%s\t", name[i]);

        free(name[i]);
    }
    printf("\n");

    /******malloc way2:*****************************************************
     *      1. malloc once for name[Row][Column] to make the malloc area continue
     *      2. then assignment the address to every name[i]
     *      3. only need free name[0]
     *************************************/
    name[0] = (char *)malloc(sizeof(char) * Row * Column);
    for (int i = 0; i < Row; i++)
    {
        name[i + 1] = name[i] + Column;
        strcpy(name[i], data[i]);
        my_trace(BRIGHT, GREEN, BLACK, "%s\t", name[i]);
    }
    printf("\n");
    free(name[0]);
    //============END=================================




/*************usage of char (*str)[N]********************************
*		char str[][N]
*	1. str is a pointer, points to the row of a 2 dimensions array, this row has N elements!
*	2. N is the first dimension of this 2 dimensions array!
*	3. p is the first address of this 2 dimensions array--str[][N]
*
********************************************************************/

#ifdef way1
	char (*name2)[Column] = NULL;
	name2 = (char (*)[Column])malloc(sizeof(char) * Row * Column);
	printf("1 --- %p\n", name2);

//	name2 = data[0];	// error!!! If name2 = data[0], why did you malloc memory? 
						// And the error will occur when you free name2;
//	free(name2);		// if name2 = data[0], then segment fault will occur!
						
	for(int i = 0; i < Row; i++)
	{
		strcpy(*(name2 + i), data[i]);
		printf("%s\n", *(name2 + i));
	}

    for (int i = 0; i < Column; i++)
    {
        printf("%c\t", *(*name2 + i));
        printf("%c\n", *(*(name2 + 1) + i));
    }
#endif

#ifdef way2
	/***********************
		DO NOT malloc! Assign data  to pointer pt.

	 ***********************/
	char (*pt)[Column] = (char (*)[Column])data[0];

	for(int i = 0; i < Row; i++, pt++)
	{
		pt = (char (*)[Column]data[i]);
		printf("");
	}
#endif
    //============END=================================

    return 0;
}

