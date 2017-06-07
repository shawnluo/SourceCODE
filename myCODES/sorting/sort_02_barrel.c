#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int arr[1001] = {0};
	int	i, j, len, num;
	len = 5;

	for(i = 0; i < len; i++)
	{
		scanf("%d", &num);
		arr[num]++;
	}
	
	for(i = 1000; i >= 0; i--)
	{
		for(j = 1; j <= arr[i]; j++)
		{
			printf("%d ", i);
		}
	}

	return 0;
}