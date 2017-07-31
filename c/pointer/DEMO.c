
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
	int id;
	char name[50]; 
	void (*initial)();
	void (*process)(int id, char *name);
	void (*destroy)();
}stu;
void initial()
{
	printf("initialization...\n");
}
void process(int id, char *name)
{
	printf("process...\n%d\t%s\n",id, name);
}
void destroy()
{
	printf("destroy...\n");
}
int main()
{
	stu *stu1;
	//在VC和TC下都需要malloc也可以正常运行，但是linux gcc下就会出错，为段错误，必须malloc
	stu1=(stu *)malloc(sizeof(stu));
	// 使用的时候必须要先初始化
	stu1->id=1000;
	strcpy(stu1->name,"xufeng");
	stu1->initial=initial;
	stu1->process=process;
	stu1->destroy=destroy;
	printf("%d\t%s\n",stu1->id,stu1->name);
	stu1->initial();
	stu1->process(stu1->id, stu1->name);
	stu1->destroy();
	free(stu1);

	return 0;
}
