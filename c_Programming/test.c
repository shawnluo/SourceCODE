
//#define demo_sscanf
//#define demo_input_1
//#define demo_pointer_1
//#define demo_pointer_2
//#define demo_Sorting_Bubble
//#define demo_array_transform
//#define demo_array_2
//#define array_char
//#define binary_tranf
//#define struct_initiation
#define xxx

#ifdef demo_sscanf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   int day, year;
   char weekday[20], month[20], dtm[100];

   strcpy( dtm, "Saturday March 25 1989" );
   sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );

   printf("%s %d, %d = %s\n", month, day, year, weekday );
    
   return(0);
}

#elif defined demo_input_1

//

#include <stdio.h>

int main(void)
{
	int hoge;
	char buf[256];

	printf("&hoge...%p\n", &hoge);

	printf("Input initial value.\n");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d", &hoge);

	while(1)
	{
		printf("hoge..%d\n", hoge);

		getchar();
		hoge++;
	}
	
	return 0;
}

#elif defined demo_pointer_1

#include <stdio.h>

int main(void)
{
	int x = 5;
	int y = 100;

	char *kk = NULL;

	printf("&x = %p\n", &x);
	printf("&y = %p\n", &y);
	
	int *p = NULL;
	printf("p = %p\n", p);

	p = &x;
	
	printf("%p\n", &x);
	printf("p = %p\n", p);

	printf("%p\n", &p);

/*
	*p = y;
	printf("%p\n", &y);
	printf("p = %p\n", p);
	printf("x = %d\n", x);
*/

	p = &y;
	*p = 787;

	printf("x = %d\n", x);
	printf("p = %p\n", p);
	printf("y = %p\n", &y);

	printf("%d, %d\n", sizeof(p), sizeof(kk));
	
	return 0;
}

#elif defined demo_Sorting_Bubble

#include <stdio.h>

int main(void)
{
	int f[20] = {1, 1};

	int i = 0, j = 0, tmp = 0;
	
	for(i = 2; i < 20; i++)
	{
		f[i] = f[i - 1] + f[i - 2];
		printf("f[%d] = %12d,", i, f[i]);
	}
	printf("\n");
	
	for(i = 0; i < 20; i++)
	{
		for(j = 0; j < 20 - i; j++)
		{
			if(f[j] < f[j + 1])	//the maxim/minmam date will float to the opposite end.
			{
				tmp = f[j];
				f[j] = f[j + 1];
				f[j + 1] = tmp;
			}
		}
	}

	for(i = 0; i < 20; i++)
	{
		printf("%d\n", f[i]);
	}

	return 0;
}

#elif defined demo_array_transform

#include <stdio.h>

int main(void)
{
	int array[10][2];
	int y[2][10];

	int i = 0, j = 0, num = 0;
	
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 2; j++)
		{
			array[i][j] = num++;
			printf("%10d", array[i][j]);
		}
		printf("\n");
	}

	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 2; j++)
		{
			y[j][i] = array[i][j];
		}
	}
	
	printf("\n");

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 10; j++)
		{
			printf("%10d", y[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
#elif defined demo_array_2

#include <stdio.h>

int main(void)
{
	int i = 0, j = 0;
	int a[3][4] = {{22, 4, 7, 9999}, {0, -324, 5, 0}, {993, 87, 431}};
	int Max = a[0][0];

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(Max < a[i][j])
			{
				Max = a[i][j];
			}
		}
	}
	printf("Max = %d\n", Max);
	
	return 0;
}

#elif defined array_char

#include <stdio.h>
int main(void)
{
	int i = 0, num = 5;
//	char c[2] = {'S', 'k', '\0', 'g', '\0'};
	char c[13] = "ok";
	
//	printf("%s\n", c);

	char a[5] = "good";

	for(i = 0; i < 13; i++)
	{
		printf("%c\n", c[i]);
	}
	
	return 0;
}

#elif defined binary_tranf

#include <stdio.h>
#include <string.h>

int main(void)
{
	int num = 1993;
	int mod_value = 0;
	int bit_value = 0;
	char array[100];
	int i = 0;
//	char *array;

//	array = (char *)malloc();
	
	while(0 != num)
	{
		bit_value = num / 2;
		mod_value = num % 2;
		num = bit_value;
		array[i] = mod_value;
//		printf("%d\n", array[i]);
		i++;
	}
	
	char str[] = {"Chinagood"};
	char *stt = "good";
//	puts(str);
	printf("%d\n", strlen(stt));

	return 0;
}

#elif defined struct_initiation

#include <stdio.h>

typedef int (*caculate_cb)(int a, int b);

typedef struct _oper {
	int a;
	int b;
	caculate_cb cal_func;
} oper;

int add(int a, int b)
{
	return (a + b);
}

int multi(int a, int b)
{
	return (a * b);
}

int main(void)
{
	int ret = 0;

	//order initiation
	oper oper_one = {10, 20, add};

	//random initiation way1
	oper oper_two = {
		.b = 30,
		.a = 20,
		.cal_func = &multi,
	};

	//random initiation way2
	oper oper_three = {
		cal_func:&add,
		a:40,
		b:20,
	};

	ret = oper_one.cal_func(oper_one.a, oper_one.b);
	printf("%d\n", ret);

	ret = oper_two.cal_func(oper_two.a, oper_two.b);
	printf("%d\n", ret);

	ret = oper_three.cal_func(oper_three.a, oper_three.b);
	printf("%d\n", ret);

	printf("%p\n", multi);	
	printf("%p\n", &multi);	

	return 0;
}

#elif defined xxx

#include <stdio.h>

int main(void)
{
	char str[50];

	int x/*blash blash */y;	
	return 0;
}

#endif
