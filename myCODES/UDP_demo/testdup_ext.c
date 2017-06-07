#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 int main(void)
 {
	int pfds[2];

	if ( pipe(pfds) == 0 )
	{
		if ( fork() == 0 )		//child
		{
			close(1);
			dup2( pfds[1], 1 );
			close( pfds[0] );
			execlp( "ls", "ls", "-1", NULL );
		}
		else
		{
			close(0);
			dup2( pfds[0], 0 );
			close( pfds[1] );
			execlp( "wc", "wc", "-l", NULL );
		}
	}

     return 0;
 }


