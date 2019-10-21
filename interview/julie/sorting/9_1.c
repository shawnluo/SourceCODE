#include <stdio.h>
#include <string.h>

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
		}
		p1[k--] = p2[j--];
	}

	return 0;
}

/*Test program To-do
 * Please print out the two arrays before meging, also print out the two arrays after merging
 */
int main(void)
{
	//Test case1: Array1 is 1,2,3,4;len is 8, Array2 is 5,6,7,8
	//Test case1: Array1 is 1;len is 2, Array2 is 2
	//Test case3: Array is 1, Array2 is NULL
	//Test case4: Array1 is NULL, Array2 is 2
	//Test case4: Array1 is NULL, Array2 is NULL
	//Test case5: Array1 is 1,2,3,4; len is 7, Array2 is 5,6,7,8 (Len is not enough to hold all elements)
}
