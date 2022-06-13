#include <stdio.h>
#include <string.h>

/*If finding the target successfully, return the idx;
 *If can not find the target, return -1.
*/
int find_target(int *arr, int start_idx, int end_idx, int target)
{
	int ret = -1;
	if(arr == NULL)
	{
		printf("\n Invalid array pointer \n");
		return -1;
	}
	int mid = (end_idx-start_idx)/2;

	if(arr[mid] == target)
	{
		printf("\n find the target successfully\n");
		return mid;
	}	
	ret = find_target(arr,start_idx,mid,target); 
	if(ret >=0)
	{
		printf("\n find the target successfully \n");
		return ret;
	}

	ret = find_target(arr,mid,end_idx,target);
	if(ret >= 0)
	{
		printf("\n find the target successfully \n");
		return ret;
	}
	printf("\n Went through all elements, have not found the target \n");
	return -1;
}

#define ARRAY_SIZE 10
int main(void)
{
	int a[10] = {0};
	int i;

	//Initalize the array
	for(i = 0;i < ARRAY_SIZE;i++)
	{
		a[i] = i;
	}	

}	
