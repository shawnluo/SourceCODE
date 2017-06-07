/*输入:cmd－包含要执行的命令的数据
 ***shell_path－用户shell的环境变量
 *输出:无
 *功能:退出shell命令解释器，释放申请的内存空间
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
extern void history_exit(void);
void exit_shell(Command *cmd,char *shell_path[])
{
	int len;
	Command *temp;
	for(len=0;shell_path[len]!=NULL&&len<SHELL_PATH_NUM;len++) {
		free(shell_path[len]);
		shell_path[len]=NULL;
	}
	while(cmd!=NULL) {
		temp=cmd;
		cmd=cmd->next_command;
		free(temp);
		temp=NULL;
	}
	history_exit();
	return;
}/*void exit_shell(Command *cmd,char *shell_path[])*/
