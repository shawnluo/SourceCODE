
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
	
	int a[4][3]= {1,2,3,4,5,6,7,8,9,10,11,12};
	  int (*prt) [3] = a, *p=a[0];

	  printf("%d\n", *( (*prt+2) [2] ));
	
	return 0;
}
