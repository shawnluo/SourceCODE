/*输入:argv-help命令的参数
 *输出:无
 *功能:实现help命令
 *作者:吴刚<xuanfeng1104@gmail.com>
 *修改:
 */
#include"head.h"
extern char help_path[CMD_PATH_LEN];
void do_help(char *argv )
{
	char cmd_argv[2][MAX_CMD_LEN];
	memset(cmd_argv[0],'\0',MAX_CMD_LEN);
	memset(cmd_argv[1],'\0',MAX_CMD_LEN);
	char  strtok_str[]=" ";
	char buf[CURRENT_PATH_LEN];
	int nread;
	int fd,i;
	char *t=(char *)malloc((strlen(argv)+1)*sizeof(char));
	char *ptr;
	char help[CMD_PATH_LEN];
	strcpy(t,argv);
	ptr=strtok(t,strtok_str);
	for(i=0;ptr!=NULL&&i<2;i++) {
		strcpy(cmd_argv[i],ptr);
		ptr=strtok(NULL,strtok_str);
	}
	if(strlen(cmd_argv[1])==0) {
		if(strcmp(cmd_argv[0],"-s")!=0)

			strcpy(cmd_argv[1],cmd_argv[0]);
		memset(cmd_argv[0],'\0',MAX_CMD_LEN);
	}
	if((strcmp(cmd_argv[0],""))==0||strcmp(cmd_argv[0],"-s")==0) {
		if(strcmp(cmd_argv[0] ,"-s")==0) {
			if((strcmp(cmd_argv[1],""))==0||(strcmp(cmd_argv[1],"kill"))==0||(strcmp(cmd_argv[1],"pwd"))==0                    \
			   ||(strcmp(cmd_argv[1],"echo"))==0||(strcmp(cmd_argv[1],"help"))==0||(strcmp(cmd_argv[1],"cd"))==0) {
				if(strcmp(cmd_argv[1],"cd")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/cd");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,1))>0)
							printf("%s",buf);
						if(strcmp(buf,"\n")==0) {
							break;
						}
					}
					return ;
				}
				else if(strcmp(cmd_argv[1],"kill")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/kill");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return ;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,1))>0)
							printf("%s",buf);
						if(strcmp(buf,"\n")==0) {
							break;
						}
					}
					return;
				}
				else if(strcmp(cmd_argv[1],"pwd")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/pwd");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,1))>0)
							printf("%s",buf);
						if(strcmp(buf,"\n")==0) {
							break;
						}
					}
					return;
				}
				else if(strcmp(cmd_argv[1],"echo")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/echo");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,1))>0)
							printf("%s",buf);
						if(strcmp(buf,"\n")==0) {
							break;
						}
					}
					return;
				}
				else if(strcmp(cmd_argv[1],"help")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/help");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,1))>0)
							printf("%s",buf);
						if(strcmp(buf,"\n")==0) {
							break;
						}
					}
					return;
				}
				else {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/null");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,256))>0)
							printf("%s",buf);
						else break;
					}
					return;
				}
			} else
				printf("bash: help: no mat\"%s\"help a subject.Try\"help help\" .\n",cmd_argv[1]);
			return;
		} else {
			if((strcmp(cmd_argv[1],""))==0||(strcmp(cmd_argv[1],"kill"))==0||(strcmp(cmd_argv[1],"pwd"))==0                    \
			   ||(strcmp(cmd_argv[1],"echo"))==0||(strcmp(cmd_argv[1],"help"))==0||(strcmp(cmd_argv[1],"cd"))==0) {
				if(strcmp(cmd_argv[1],"cd")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/cd");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,256))>0)
							printf("%s",buf);
						else break;
					}
					return;
				}
				else if(strcmp(cmd_argv[1],"kill")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/kill");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,256))>0)
							printf("%s",buf);
						else break;
					}
					return;
				}
				else if(strcmp(cmd_argv[1],"pwd")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/pwd");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,256))>0)
							printf("%s",buf);
						else break;
					}
					return;
				}
				else if(strcmp(cmd_argv[1],"echo")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/echo");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,256))>0)
							printf("%s",buf);
						else break;
					}
					return;
				}
				else if(strcmp(cmd_argv[1],"help")==0) {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/help");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,256))>0)
							printf("%s",buf);
						else break;
					}
					return;
				}
				else {
					strcpy(help,help_path);
					strcat(help,"/src/helpfile/null");
					if((fd=open(help,O_RDWR))==-1) {
						perror("Could not open file\n");
						return;
					}
					lseek(fd ,0,SEEK_SET);
					while(1) {
						memset(buf,'\0',256)  ;
						if((nread=read(fd,buf,256))>0)
							printf("%s",buf);
						else break;
					}
					return;
				}
			} else    
				printf("bash: help: no mat\"%s\"help a subject.Try\"help help\" .\n",cmd_argv[1]);
			return;
		}

	} else 
		printf("bash: help: argv: void options\nhelp: usage: help [-s] [pattern . . .]");
	return;
}/*输入:argv-help命令的参数
 *输出:无
 *功能:实现help命令
 *作者:吴刚<xuanfeng1104@gmail.com>
 *修改:
 */
