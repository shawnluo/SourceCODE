#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
	int id;
	char *name;
	struct student *next;
} STU;

#define LEN sizeof(STU)

STU *creat_Linklist()
{
	int i = 0;
	STU *head;
	head = (STU*)malloc(LEN);
	head->id = 3;
	head->name = "good";
	head->next = NULL;
	
//	printf("name:\t%s\n", head->name);
//	printf("id:\t%d\n", head->id);

	STU *p1, *p2;
	p1 = p2 = head;

	while(i++ < 4)
	{
		p1 = (STU *)malloc(LEN);
		p1->id = i * 100;
		p2->next = p1;
		p2 = p1;
	}
	p1 = NULL;
	
	return head;
}


STU *insert_Linklist(STU *head)
{
	STU *p1, *p2, *tmp;
	int NUM = 300;

	p1 = head;

	if(p1->id == NUM)
	{
		p1 = (STU *)malloc(LEN);
		p1->id = 6000;
		p1->next = head;
		head = p1;
	}
	
	while(p1->next->id != NUM)
	{		
		p1 = p1->next;
	}

	if(p1 != NULL)
	{
//		printf("\t%d\n", p1->id);
		tmp = p1->next;

		p2 = (STU *)malloc(LEN);
		p2->id = 6000;
		p2->next = p1->next;
		p1->next = p2;
	}
	
	return head;
}

void free_Linklist(STU *head)
{
	STU *p1 = head, *p2;

	while(p1->next != NULL)
	{
		p2 = p1->next;
		free(p1);
	}
	
	return head;
}

void showme(STU *head)
{
	STU *p = head;

	if(p == NULL)
	{
		printf("empty list!\n");

		return;
	}
	
	while(p != NULL)
	{
		printf("\t%d\n", p->id);
		p = p->next;
	}
}

int main(void)
{
	STU s1 = 
		{16, "shawn"};

//	printf("name: \t%s\n", s1.name);

	STU *head, *p;

	head = creat_Linklist();
//	showme(head);

	head = insert_Linklist(head);
	showme(head);

	free_Linklist(head);
	showme(head);
	
	return 0;
}
