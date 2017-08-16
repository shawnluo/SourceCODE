
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
#include "color.h"


void print_trace()
{
    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}

/***************************************************************************************
 *	write a general purpose function, calculate (0, 1)sinxdx, (-1, 1)cosxdx, (0, 2)exdx.
 ****************************************************************************************/
 
float integral(float (*p)(float), float a, float b, int n)
{
    int   i;
    float x, h, s;

    h = (b - a) / n;
    x = a;
    s = 0;
    for (i = 0; i < n; i++)
    {
        x = x + h;
        s = s + (*p)(x) * h;
    }
    return(s);
}

float fsin(float x)
{
    return sin(x);
}
float fcos(float x)
{
    return cos(x);
}
float fexp(float x)
{
    return exp(x);
}




int main(void)
{
    float a1, b1, a2, b2, a3, b3, c, (*p)(float);
    int   n = 20;
	
    printf("enter a1,b1: ");                   
    scanf("%f %f", &a1, &b1);
	
    printf("enter a2,b2: ");
    scanf("%f %f", &a2, &b2);
	
    printf("enter a3,b3: ");
    scanf("%f %f", &a3, &b3);

    p = fsin;
    c = integral(p, a1, b1, n);
    printf("sin(x)=%f\n", c);

    p = fcos;
    c = integral(p, a2, b2, n);
    printf("cos(x)=%f\n", c);

    p = fexp;
    c = integral(p, a3, b3, n);
    printf("exp(x)=%f\n", c);

    return 0;
}


typedef (*fun)(float);


void myFun(float i)
{
	printf("%f\n", i);
}

float intergral(float (*fun)(float), )
{

}

int main(void)
{
	float ret;

	fun Fun = myFun;

	Fun(10.9809);

	ret = integral(fun);

	return 0;
}
