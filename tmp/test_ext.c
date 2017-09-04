
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include "math.h"

#include <stdbool.h>
//#include "color.h"


/*************************
*		wrong cases
*************************/
//#define w_01	//wrong case NO.01		strcpy before malloc
//#define w_02	//wrong case NO.02		strncpy pointer cross-border
//#define w_03	//wrong case NO.03		try to get the length of a interger pointer array.

/*************************
*		demo
*************************/
//#define d_01	//show the usage of strcpy and strncpy
//#define d_02	//find and return the substring
//#define d_03	//bit operations
//#define d_04	//find the addtional charater
//#define d_05	//linklist and sorting
//#define d_06	//quick sorting
//#define d_07	//Is_Palindrome
//#define d_08	//2 linklists adding with carry bit
//#define d_09	//substring or not

//#define test_pre
#define test
//#define test_2
//#define test_3


void print_trace()
{
//    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}

#ifdef test

int main(void)
{
	char s[] = "goiday";
//	char k[10];
	memmove(s + 1, s + 2, 5);
	printf("%s\n", s);
	return 0;
}

#endif
