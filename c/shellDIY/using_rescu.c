#if defined (HAVE_CONFIG_H)
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#define STD_IN 0
#define STD_OUT 1
#define MAXORD  200
#define MAXPARA 8

extern void exit();
extern HIST_ENTRY **history_list ();

char *trim(const char *str);
int pipel(const char *cmd);
int redirect(const char *cmd);
int is_back(char *order);
void do_cd(char *argv[]);
char *if_exist(char *order);
void pr_prompt(void);
static void sig_int(void);

char *all_order, *order[MAXORD];
int i,ret,pid,status,number=1,back;
char *test_prev;
char *test[MAXPARA];
char prompt[MAXORD + 1];
struct sigaction act;

void main(void)
{
	int done;

	all_order = (char *)NULL;
	done = 0;

	act.sa_handler = sig_int;
	act.sa_flags = SA_NOMASK;
	sigaction(SIGINT, &act, NULL);
	//readline.parse_and_bind("tab:complete");
	//rl_bind_key('\t', rl_insert);
	//initialize_readline();

	printf("-------------*Welcome*-------------\n");

	while(!done)
	{
		pr_prompt();
		all_order = readline (prompt);

		if (*all_order)
		{
			add_history (all_order);
		}
		if(all_order == NULL || trim(all_order) == NULL)
		{
			continue;
		}
		back = is_back(trim(all_order));
		
		if(strcmp(trim(all_order), "exit")==0)
		{
			printf("-------------*Goodbye*-------------\n");
			done = 1;
		}
		order[0] = trim(strtok(all_order,"&"));
		//printf("param:%s\n", order[0]);
		for(i=1; (order[i]=trim(strtok(NULL,"&")))!=NULL; i++)
		{
			number++;
			printf("number:%d\n", number);
		}
		for(i=0;i<number-1;i++)
		{
			if(fork() == 0)
			{
				pipel(order[i]);
			}
		}
		//printf("0@\n");
		test_prev = strdup(order[0]);
		if( strcmp( test[0] = trim(strtok(test_prev, " ")), "cd" ) == 0 )
		{
			//printf("3@\n");
			test[1] = trim(strtok(NULL," "));
			do_cd(test);
			continue;
		}

		//printf("1@\n");
		if((pid=fork())==0)
		{
			pipel(order[i]);
			exit(0);
		}
		else
		{
			if(back==0)
			{
				waitpid(pid, &status, 0);
			}
		}
		number=1;
		free(all_order);
	}
}

static void sig_int(void)
{
    printf("\n");
    pr_prompt();
}

/*print shell*/
void pr_prompt(void)
{
       /*prompt format: "[user@host: pwd]$ " */
       
       char host[MAXORD + 1],
            pwd[MAXORD + 1];
       size_t len;
    
       gethostname(host, MAXORD);
    
       getcwd(pwd, MAXORD);
       len = strlen(getenv("HOME"));

       sprintf(prompt, "[%s@%s: %s]$ ", getenv("LOGNAME"), host, pwd);
       //printf("%s", prompt);
}

int pipel(const char *cmd)
{
	printf("cmd = %s\n", cmd);
	
	int i, fd[2], status, pid, back;
	char *order, *other;
	/*将第一条命令与后面的命令分开来*/

	order = trim(strtok(cmd, "|"));		//show me > dd.txt | the money | yes | good
	other = trim(strtok(NULL, ""));		//the money | yes | good
	//printf("1@\n");
	if(!other)
	{
		//printf("2@\n");
		redirect(order);
	}
	else
	{
		pipe(&fd[0]);
		if((pid=fork()) == 0)		//child
		{
			printf("order = %s\n", order);
			close(fd[0]);
			close(STD_OUT);
			dup(fd[1]);
			close(fd[1]);
			
			redirect(order);        /*执行第一条没有用到管道的命令*/
		}
		else
		{
			close(fd[1]);              
			close(STD_IN);
			dup(fd[0]);
			close(fd[0]);
			waitpid(pid, &status, 0);
			
			printf("other = %s\n", other);
			pipel(other);        /*执行后面的命令*/
		}
	}
	return 1;
}

int redirect(const char *cmd)		//cmd = "ls -l > dd.txt"
{
       char *trim(const char *str);
       void do_cd(char *argv[]);
       char *order=trim(cmd),*order_path,*real_order;
       char *infile,*outfile,*arg[MAXPARA],*buffer;
       int i,type=2,para_num,fd_out,fd_in,pid,status;

       /*数字含义：    3: < infile

                     4: > outfile

                     5: > outfile < infile

                    6: < infile  > outfile    */
       for(i=0;i<strlen(cmd);i++)
	   {
              if(cmd[i]=='<')
              {
                     type++;
              }
              if(cmd[i]=='>')
              {
                     type=type*2;
              }
       }
       if(type==3 || type==6)
       {
              real_order=trim(strtok(cmd,"<"));
       }
       else if(type==4 || type==5)
       {
              real_order=trim(strtok(cmd,">"));
       }
       else if(type==2)
       {
              real_order=trim(cmd);
       }
       else
	   {
              fprintf(stderr,"#error: bad redirection form\n");
              return -1;
       }
       /*获取指令参数*/
       arg[0]=trim(strtok(real_order," "));
       for(i=1;(arg[i]=trim(strtok(NULL," ")))!=NULL;i++)
	   {
			;
       }
       if((order_path=if_exist(arg[0]))==NULL)
	   {
              fprintf(stderr,"#error: this command doesn't exist\n");
              return -1;
       }
       switch(type)
	   {
              case 2:
                     break;
              case 3:
                     buffer=strtok(order,"<");
                     infile=trim(strtok(NULL,""));
                     break;
              case 4:
                     buffer=strtok(order,">");
                     outfile=trim(strtok(NULL,""));
                     break;
              case 5:
                     buffer=strtok(order,">");
                     outfile=trim(strtok(NULL,"<"));
                     infile=trim(strtok(NULL,""));
                     break;
              case 6:
                     buffer=strtok(order,"<");
                     infile=trim(strtok(NULL,">"));
                     outfile=trim(strtok(NULL,""));
                     break;
              default:
                     return -1;
       }
       /*创建输出文件并将指令的标准输出定向到该文件*/

       if(type==4 || type==5 || type==6)
	   {
              if((fd_out=creat(outfile, 0755))==-1)
			  {
                     fprintf(stderr,"#error: redirect standard out error\n");
                     return -1;
              }
              close(STD_OUT);
              dup(fd_out);
              close(fd_out);
       }
       /*将输入文件定向到指令的标准输入*/
       if(type==3 || type==5 || type==6)
	   {
              if((fd_in=open(infile,O_RDONLY,S_IRUSR|S_IWUSR))==-1)
			  {
                     fprintf(stderr,"#error: can't open inputfile '%s'\n",infile);
                     return -1;
              }
              close(STD_IN);
              dup(fd_in);
              close(fd_in);
       }
       //printf("bug%s  \n", order_path);
       //printf("bug2 %s  %s \n", arg[0], arg[1]);
       
       if (strcmp(arg[0], "ls") == 0 && arg[1] == NULL)
	   {
              //printf("4@%s\n", arg[1]);
              static  DIR  *dir;
              struct   dirent   *entry;
              char *name ,i;
              char pwd[MAXORD + 1];

              getcwd(pwd, MAXORD);
              dir = opendir(pwd);
              if(!dir)
              {
                   printf("Can't   open   %s\n", pwd);
              }
              int flag = 0;
			  
              for(i=0;i<100;i++)
			  {
                   if((entry = readdir(dir)) == NULL)   
				   {
                        closedir(dir);
                        dir = 0;
                        //printf("\n");
                        return 1;
                   }
                   name=entry->d_name;
                   struct stat statbuf;
                   stat(name, &statbuf);
                   if( name[0] != '.' && strstr(name,"~") == NULL)
				   {
                        flag++;
                        char *ptr;
                        if (S_ISDIR(statbuf.st_mode))
                              ptr = "directory";
                        else if (S_ISCHR(statbuf.st_mode))
                              ptr = "character special";
                        else if (S_ISBLK(statbuf.st_mode))
                              ptr = "block special";
                        else if (S_ISFIFO(statbuf.st_mode))
                              ptr = "fifo";
#ifdef S_ISLINK
                        else if (S_ISLNK(statbuf.st_mode))
                              ptr = "symbolic link";
#endif
#ifdef S_ISSOCK
                        else if (S_ISSOCK(statbuf.st_mode))
                              ptr = "socket";
#endif
                        else if (S_IEXEC & statbuf.st_mode)
                              ptr = "exec";
                        else if (S_ISREG(statbuf.st_mode))
                              ptr = "regular";
                        else
                              ptr = "** unknown mode  **";

                        if (strcmp(ptr, "directory") == 0)
                              printf("\033[1;34m%s\033[0m\n", name);
                        else if (strcmp(ptr, "exec") == 0)
                              printf("\033[1;32m%s\033[0m\n", name);
                        else
                              printf("%s\n", name);
                        if (flag == 3)
						{
                             //printf("\n");
                             flag = 0;
                        }
                   }
              }
       }
	   else
	   {
              execv(order_path,arg);
       }
       return 1;
}

/*void  printdir(char *dir){
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	
	char buf[1024];
	if (getcwd(buf,sizeof(buf)) == NULL){
		exit(1);
	}
	if ((dp = opendir(dir)) == NULL){
		fprintf(stderr,"can not open directory: %s\n",dir);
		return ;
	}
	chdir(dir);
	while ((entry = readdir(dp)) != NULL){
		lstat(entry->d_name,&statbuf);
		if (strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0 || entry->d_name[0] == '.')
			continue;
		show_ls(entry->d_name,&statbuf);
	}
	chdir(buf);
	closedir(dp);
}*/

/*判断指令的结尾有无'&'*/

int is_back(char *order)
{
       int len=strlen(order);
       if(order[len-1]=='&')
	   {
              order[len]='\0';
              return 1;
       }
       else
              return 0;

}

/*判断目录是否存在*/

void do_cd(char *argv[])
{
       //printf("4@:%s\n", argv[1]);
       if ((argv[1] == NULL) || (strcmp(argv[1], "~") == 0) )
	   {
           argv[1] = "/home/tom";
       }
       if(argv[1]!=NULL)
	   {
              if(chdir(argv[1])<0)
			  {
                     switch(errno)
					 {
                            case ENOENT:
                                   fprintf(stderr,"#error: directory can't be found\n");
                                   break;
                            case ENOTDIR:
                                   fprintf(stderr,"#error: this is not a directory name\n");
                                   break;
                            case EACCES:
                                   fprintf(stderr,"#error: you have no right to access\n");
                                   break;
                            default:
                                   fprintf(stderr,"#error: unknown error\n");
                     }
              }
       }
}

/*判断系统调用是否存在*/
char *if_exist(char *order)
{
       char *all_path,*p,*path,*buffer;
       int i=0,len;
       all_path=getenv("PATH");
       buffer=trim(all_path);
       len=strlen(all_path)+strlen(order);
       if((path=(char *)malloc(len*(sizeof(char))))==0){
              fprintf(stderr,"#error: can't malloc enough space for buffer\n");
              return NULL;
       }
       p=strtok(buffer,":");
       while(p){
              strcat(strcat(strcpy(path,p),"/"),order);
              if(access(path,F_OK)==0){
                     return path;
              }
              p=strtok(NULL,":");
       }
       strcpy(path,order);
       if(access(path,F_OK)==0)
              return path;
       return NULL;
}


/*裁去字符串首尾空格*/
char *trim(const char *str)
{
	int i,j,k;
	char *order;
	if(str==NULL)
	{
		return NULL;
	}
	
	for(i=0;i<strlen(str);i++)		/*从字符串最开始找到非空格位置*/
	{
		if(str[i]!=' ')
		{
			break;
		}
	}
	for(j=strlen(str)-1;j>-1;j--)	/*从字符串最后找到非空格位置*/
	{
		if(str[j]!=' ')
		{
			break;
		}
	}
	if(i<=j)
	{
		if((order=(char *)malloc((j-i+2)*(sizeof(char))))==0)		/*	申请空间大小为: 去掉空格后的字符+'\0'	*/
		{
			fprintf(stderr,"#error: can't malloc enough space\n");
			return NULL;
		}
		for(k=0;k<j-i+1;k++)
		{
			order[k]=str[k+i];		/*将去掉了前后空格的字符拷贝到order*/
		}
		order[k]='\0';
		return order;
	}
	else
		return NULL;		/*如果全是空格*/
}

