#include <stdio.h>
#include <string.h>


/*
Return value:
0:  Did NOT find the element in the given array
1:  Yes, find the element in the given array
-1: The input parameter is invalid
*/
int FindElement(int *pArr, int start, int end, int element, int *idx)
{
	int center=0;
	int ret = 0;
	if((pArr == NULL)
		||(start < 0)
		||(end < 0)
		||(Idx == NULL)
		||(start < end))
	{
		return -1;
	}
	if(start < end)
	{
		center = (start + end) / 2;
		ret = FindElement(pArr,start,center,element,idx);
		if(ret != 0)
		{
			ret = FindElement(pArr,center,end,element,idx);
		}
		return ret;
	}
	else
	{
		if(pArr[start] == element)
		{
			ret = 1;
		}
		else
		{
			ret = 0;
		}
	}
	return ret;
}


/*
Test program: To-do
*/
int main(void)
{
	/*Test case 1(odd length) 
	part1: Given array(1,2,3,4,5), find element 1
	part2: Given array(1,2,3,4,5), find element 5
	part3: Given array(1,2,3,4,5), find element 2
	part4: Given array(1,2,3,4,5), find element 3
	part4: Given array(1,2,3,4,5), find element 4
	part5:  Given array(1,2,3,4,5), find element 8
	*/

	/*Test case 2(even length):
	part1: Given array(1,2,3,4,5,6), find element 1
	part2: Given array(1,2,3,4,5,6), find element 6
	part3: Given array(1,2,3,4,5,6), find element 2
	part4: Given array(1,2,3,4,5,6), find element 5
	part5: Given array(1,2,3,4,5,6), find element 3
	part6: Given array(1,2,3,4,5,6), find element 4
	part6: Given array(1,2,3,4,5,6), find element 8
	*/
	

	return 0;
}
