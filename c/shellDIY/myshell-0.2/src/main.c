/*
 *功能：负责调度整个shell 执行的流程
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
char internal_cmd[INTERNAL_CMD_NUM][5]={"cd","echo","help","pwd","kill"};
char user_home[80];
char help_path[CMD_PATH_LEN];
extern void init_shell (char *current_path,char **shell_path);
extern void init_command(Command *cmd);
extern void print_prompt(char *current_path,char *print_str);
extern boolean read_command(Command *cmd,char *print_str);
extern boolean split_command(Command *cmd);
extern void correction_cmd(Command *cmd);
void find_file( Command *cmd,char *current_path,char *shell_path[] );
extern boolean do_cmd(Command *cmd,char *current_path);
extern void current_exit(Command *cmd);
extern void exit_shell(Command *cmd,char *shell_path[]);
int main()
{
	Command *cmd;		/*全局变量*/
	char current_path[CURRENT_PATH_LEN];  /*当前shell的路径*/
	char *shell_path[SHELL_PATH_NUM];    /*用户shell环境变量*/
	char print_str[CMD_PATH_LEN];
	/*char *current_path;*/

	cmd=(Command *)malloc(sizeof(Command));
	if(!cmd) {
		fprintf(stderr,"malloc error...\n");
		exit(1);
	}
	/*current_path=(char *)mmap(NULL,sizeof(char)*CURRENT_PATH_LEN,
		PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	*/
	init_shell(current_path,shell_path);

	while(TRUE) {
		init_command(cmd);
		print_prompt(current_path,print_str);
		if(!read_command(cmd,print_str))
			continue;
		if((strcmp(cmd->full_cmd,"quit"))==0)
			break;

		if(!split_command(cmd))
			continue;
		correction_cmd(cmd);

		find_file(cmd,current_path,shell_path);

		do_cmd(cmd,current_path);
		current_exit(cmd);
	}
	/*munmap(current_path,sizeof(char)*CURRENT_PATH_LEN);*/
	exit_shell(cmd,shell_path);
	return 0;

}

