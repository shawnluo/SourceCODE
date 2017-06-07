
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
	//��VC��TC�¶���ҪmallocҲ�����������У�����linux gcc�¾ͻ����Ϊ�δ��󣬱���malloc
	stu1=(stu *)malloc(sizeof(stu));
	// ʹ�õ�ʱ�����Ҫ�ȳ�ʼ��
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
