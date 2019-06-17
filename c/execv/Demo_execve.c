
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int ret;
	char *arg[] = {"env", NULL};
	char *envp[] = {"PATH=/tmp", "USER=WanGWensong", NULL};
	if(!fork())
	{
		if(execve("/usr/bin/env", arg, envp) < 0)
		{
			printf("Execve error!\n");
		}
	}

	return 0;
}