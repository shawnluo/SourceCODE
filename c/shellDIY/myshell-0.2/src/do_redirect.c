/*输入:cmd-包含要执行的命令的数据
 *输出:无
 *功能:执行shell的输入重定向命令。
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
void do_input_redirect(Command *cmd)
{
	int input_fd;
	if((input_fd = open ( cmd->redirect_file_name, O_RDONLY))<0) {
		perror("open");
		exit(ERROR);
	}

	dup2( input_fd, 0);
	close( input_fd);
	if((execl(cmd->cmd_path[0],cmd->cmd[0],
			  (strlen(cmd->argv[0])==0?NULL:cmd->argv[0]),(char *)0))<0) {
		perror("execl");
		exit(ERROR);
	}
	return;
}/*void do_input_redirect (Command *cmd)*/

/*输入:cmd-包含要执行的命令的数据
 *输出:无
 *功能:执行shell的输入重定向命令。
 */
void do_output_redirect(Command *cmd)
{
	int output_fd;
	if((output_fd = open (cmd->redirect_file_name, O_WRONLY|O_CREAT))<0) {
		perror("open");
		exit(ERROR);
	}

	if(chmod(cmd->redirect_file_name,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) {
		fprintf(stderr,"MyShell:Permission denied\n");
		return;
	}
	dup2( output_fd, 1);
	close( output_fd);
	if((execl(cmd->cmd_path[0],cmd->cmd[0],
			  (strlen(cmd->argv[0])==0?NULL:cmd->argv[0]),(char *)0))<0) {
		perror("execl");
		return;
	}
	return;
}/*void do_output_redirect(command cmd)*/

