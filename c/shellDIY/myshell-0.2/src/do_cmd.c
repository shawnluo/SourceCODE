/*输入：cmd－包含要执行的命令的数据。
 *char *internal_cmd[5]={"cd","echo","help","pwd","kill"};内部命令
 *输出：如果正确执行则返回TRUE.
 *功能：执行一般shell命令。
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
extern void do_internal_cmd(Command *cmd,char *cur_path);
extern void do_pipeline(Command *cmd);
extern void do_input_redirect(Command *cmd);
extern void do_output_redirect(Command *cmd);
extern void do_back_ground(Command *cmd);

void do_normal_cmd(Command *cmd,char *cur_path)
{

	if(strcmp(cmd->cmd_path[0],"internal_cmd")==0)
		do_internal_cmd(cmd,cur_path);

	else {
		if(!fork()) {
			if((execl(cmd->cmd_path[0],cmd->cmd[0],(strlen(cmd->argv[0])==0?NULL:cmd->argv[0]),NULL))<0) {
				fprintf(stderr,"Myshell:Command not find\n");
				exit(ERROR);
			}
			exit(0);
		}

		wait(NULL);
	}
	return ;
}/*void do_normal_cmd(Command *cmd)*/


/*输入:cmd-包含要执行的命令的数据
 *输出:如果命令正确执行则返回TRUE
 *功能:执行shell的复杂命令。
 */
void do_complex_cmd(Command *cmd)
{
	if((system(cmd->full_cmd))==0) {
		perror("system:l");
		exit(ERROR);
	}
	return ;
}/*void do_complex_cmd(Command *cmd)*/

/*输入:cmd-包含要执行的命令的数据
 *输出:如果命令正确执行则返回TRUE，否则返回
 *功能:执行shell命令。
  *作者：牛涛<niutao0602@gmail.com>
 */
boolean do_cmd(Command *cmd,char *cur_path)
{
	Command *L=cmd;
	while(L!=NULL) {
		switch(L->cmd_status) {
		case -1:
			/*if(cmd->cmd[0]!='\0')
			        fprintf(stderr,"%s:command error!...\n",cmd->full_cmd);
			        */
			break;
		case  0:
			do_normal_cmd(cmd,cur_path);
			break;
		case  1:
			if(!fork()) {
				if(cmd->is_input_redirect)
					do_input_redirect(cmd);
				else if(cmd->is_output_redirect)
					do_output_redirect(cmd);
				else if(cmd->is_pipeline)
					do_pipeline(cmd);
				else if(cmd->is_backgroud)
					do_back_ground(cmd);
				exit(0);
			}
			wait(NULL);
			break;
		case  2:
			do_complex_cmd(cmd);
			break;
		}
		L=L->next_command;
	}

	return TRUE;
}/*boolean do_cmd(Command *cmd)*/

