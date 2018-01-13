#include <stdio.h>
#include <string.h>
int main(void) 
{
	FILE *fp;
	char buf[150];
	char *arecord="good day\n";
	strcpy(buf,arecord); 
	
	if ((fp=fopen("log","a"))==NULL)
	{
		printf("\ncan't open file:./log");
	}
	
	fwrite(buf,strlen(buf),1,fp);
	fclose(fp);

	return 0;
}

