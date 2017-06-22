/*
 * =====================================================================================
 *       Filename:  setup.c
 *    Description:
 *        Version:
 *        Created:
 *         Author:  Sara
 * =====================================================================================
 */
#include "sshell.h"

int setup_command(char *command, char **parameters)
{
    extern struct passwd *pwd;

    if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0)
    {
        exit(0);
    }
    else if (strcmp(command, "about") == 0)
    {
#ifdef DEBUG
        printf("This is a simulation of shell (bash) in Linux.\n");
#endif
        return 1;
    }
    else if (strcmp(command, "cd") == 0)
    {
        char *cd_path = NULL;
        //memset(inputBuffer,0,sizeof(inputBuffer));

        if (parameters[1][0] == '~')
        {
            cd_path = malloc(strlen(pwd->pw_dir) + strlen(parameters[1]));
            //'~' makes length 1 more,but instead of '\0'
            if (cd_path == NULL)
            {
#ifdef DEBUG
                printf("cd:malloc failed.\n");
#endif
            }
            strcpy(cd_path, pwd->pw_dir);
            strncpy(cd_path + strlen(pwd->pw_dir), parameters[1] + 1, strlen(parameters[1]));
#ifdef DEBUG
            printf("path with ~:\n%s\n", cd_path);
#endif
        }
        else
        {
            cd_path = malloc(strlen(parameters[1] + 1));
            if (cd_path == NULL)
            {
#ifdef DEBUG
                printf("cd:malloc failed.\n");
#endif
            }
            strcpy(cd_path, parameters[1]);
        }
        if (chdir(cd_path) != 0)
        {
            printf("-sshell: cd: %s:%s\n", cd_path, strerror(errno));
        }
        free(cd_path);

		return 1;
    }
    else if (strcmp(command, "dir") == 0)
    {
        char *showdir = NULL;
//		strcpy(showdir, "ls");
//		strncpy(cd_path+strlen(pwd->pw_dir),parameters[1]+1,strlen(parameters[1]));
//      system("ls");
    }
    else if (strcmp(command, "clr") == 0)
    {
        system("clear");
		return 1;
    }
	else if (strcmp(command, "environ") == 0)
	{
		char buf[1024];
		memset(buf, 0, sizeof(buf));
	    int  count;

	    count = readlink( "/proc/self/exe", buf, 1024 );

	    if ( count < 0 || count >= 1024 )
	    {
	        printf( "Failed\n" );
	        return( EXIT_FAILURE );
	    }

	    buf[ count ] = '\0';
//	    printf( "/proc/self/exe ->; [%s]\n", buf );
		setenv("shell", buf, 1);
		
		system("env");
		unsetenv("shell");
		return 1;
	}
	else if (strcmp(command, "pause") == 0)
	{
		system("suspend -f");
		
		return 1;
	}
	else if (strcmp(command, "help") == 0)
	{
		system("help | more");
		
		return 1;
	}
	else if (strcmp(command, "pause") == 0)
	{
//		system("read -n1 -p "Press "");
		system("read -n1");
		
		return 1;
	}
	
    return 0;
}
