#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
	int id;
	char *name;
	struct student *p;
} STU;

int main(void)
{
	STU s1 = 
		{16, "shawn"};

	printf("name: %s\n", s1.name);

	creat_Linklist();
	//STU *s2 =
	//	{};
			
	return 0;
}
