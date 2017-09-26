#include <stdio.h>

extern int y;
int main(void)
{
	int x = 2;
	x = y + 1;

	printf("x = %d\n", x);
	return 0;
}
