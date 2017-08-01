
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int (*pFun)(char, char);

int FunA(char a, char b)
{
	printf("In FunA! a: %c, b: %c\n", a, b);

	return 0;
}

int FunB(char a, char b)
{
	printf("In FunB! a: %c, b: %c\n", a, b);

	return 0;
}

int main() 
{
	pFun fun;
	fun = FunA;
	fun('T', 'X');

	fun = FunB;
	fun('W', 'S');
	
	return 0;
}



