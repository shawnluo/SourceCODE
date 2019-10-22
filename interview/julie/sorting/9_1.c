#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int ShowMe(int *pArr, int Len)
{
	int i = 0;
	for(i = 0; i < Len; i++)
	{
		printf("%d\t", pArr[i]);
	}
	printf("\n");
}


/*6:14PM-6:27PM Finish the coding */
int Merge_Two_Array(int *pArrA, int Len_A, int *pArrB, int Len_B)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int *p1 = NULL;
	int *p2 = NULL;

	if((pArrA == NULL)
	  ||(pArrB == NULL)
          ||(Len_A < 0)
          ||(Len_B < 0))
         {
		return -1;
	 }		 

	printf("ArrA:\n");
	ShowMe(pArrA, Len_A);

	i = Len_A-1;
	j = Len_B-1;
	p1 = pArrA;
	p2 = pArrB;
	k = Len_A + Len_B -1;
	while((i >=0) && (j >= 0))
	{
		if(k < 0)
		{
			printf("\n The len of array is NOT enough to hold all elements ! \n");
			return -1;
		}
		if(p1[i] >= p2[j])
		{
			p1[k--] = p1[i--];
		}
		else
		{
			p1[k--] = p2[j--];
		}
	}
	ShowMe(pArrA, Len_A + Len_B);

	while(i >=0)
	{
		if(k < 0)
		{
			printf("\n The len of array1 is not enough to hold all elements! \n");
			return -1;
		}
		p1[k--] = p1[i--];
	}	

	while(j >= 0)
	{
		if(k < 0)
		{
			printf("\n The len of array1 is not engouth to hold all elements! \n");
			return -1;
		}
		p1[k--] = p2[j--];
	}

	printf("ArrA - after:\n");
	ShowMe(p1, Len_A + Len_B);

	return 0;
}

/*Test program To-do
 * Please print out the two arrays before meging, also print out the two arrays after merging
 */
int main(void)
{
#if 0
	//Test case1: Array1 is 1,2,3,4;len is 8, Array2 is 5,6,7,8
	// if len of Array1 is 8, Array1[8] = {1, 2, 3, 4, 0, 0, 0, 0}. then we need sort Array1 first.

	int Array1[100] = {1, 2, 3, 4};		// Array1 size MUST bigger than 8+4, otherwise the new merged array size will bigger than the array size. the error "stack smashing detected" will occur!!!
	int Array2[4] = {5, 6, 7, 8};
	printf("ret = %d\n", Merge_Two_Array(Array1, 8, Array2, 4));
#endif

#if 0
	//Test case1: Array1 is 1;len is 2, Array2 is 2
	// if len of Array1 is 2, Array1[2] = {1, 0}. then we need sort Array1 first.
	int Array1[100] = {1};
	int Array2[1] = {2};
	printf("ret = %d\n", Merge_Two_Array(Array1, 2, Array2, 1));
#endif

#if 0
	//Test case3: Array is 1, Array2 is NULL
	int Array1[100] = {1};
	int *Array2 = NULL;
	printf("ret = %d\n", Merge_Two_Array(Array1, 1, Array2, 1));
#endif

#if 0
	//Test case4: Array1 is NULL, Array2 is 2
	int *Array1 = NULL;
	int Array2[1] = {2};
	printf("ret = %d\n", Merge_Two_Array(Array1, 1, Array2, 1));
#endif

#if 0
	//Test case4: Array1 is NULL, Array2 is NULL
	int *Array1 = NULL;
	int *Array2 = NULL;
	printf("ret = %d\n", Merge_Two_Array(Array1, 1, Array2, 1));
#endif

#if 0
	//Test case5: Array1 is 1,2,3,4; len is 7, Array2 is 5,6,7,8 (Len is not enough to hold all elements)
	int Array1[100] = {1, 2, 3, 4};
	int Array2[] = {5, 6, 7 ,8};
	printf("ret = %d\n", Merge_Two_Array(Array1, 4, Array2, 4));
#endif

	return 0;
}
