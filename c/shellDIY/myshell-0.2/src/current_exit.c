/*输入:cmd－包含要执行的命令的数据
 *输出:无
 *功能:释放本次命令解析申请的内存空间
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
void current_exit(Command *cmd)
{
	Command *temp,*Head=cmd;
	if(Head->next_command==NULL)
		return;
	Head=temp=Head->next_command;
	cmd->next_command=NULL;
	while(temp!=NULL) {
		Head=Head->next_command;
		free(temp);
		temp=NULL;
		temp=Head;
	}
	return;
}
