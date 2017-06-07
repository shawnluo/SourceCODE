/*输入:*cmd－包含要执行的命令的数据。
 *    *cur_path－当前的工作目录
 *输出：无
 *功能：执行内部命令
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
extern void do_cd(Command *cmd, char *cur_path);
extern void do_echo(Command *cmd);
extern void do_help(char *argv);
extern void do_pwd(void);
extern void do_kill(void);
extern char internal_cmd[INTERNAL_CMD_NUM][5];

void do_internal_cmd(Command *cmd,char *cur_path)
{
	if((strcmp(cmd->cmd[0],internal_cmd[0]))==0)
		do_cd(cmd,cur_path);
	else if((strcmp(cmd->cmd[0],internal_cmd[1]))==0)
		do_echo(cmd);
	else if((strcmp(cmd->cmd[0],internal_cmd[2]))==0)
		do_help(cmd->argv[0]);
	else if((strcmp(cmd->cmd[0],internal_cmd[3]))==0)
		do_pwd();
	else if((strcmp(cmd->cmd[0],internal_cmd[4]))==0)
		do_kill();
	/*int i;
	for(i=0;i<MAX_CMD_NUM;i++)
		if((strcmp(internal_cmd[i].cmd,cmd->cmd[0]))==0)
			internal_cmd[i].do_cmd();
	*/
	return;
}
