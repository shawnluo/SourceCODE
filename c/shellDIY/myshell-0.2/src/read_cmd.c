/*输入:cmd－包含要执行的命令的数据
 *    str－显示的提示符    
 *输出:无
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
boolean read_command(Command *cmd,char *str)
{
	char *read_string;
	read_string=readline(str);
	if(read_string&&*read_string) {
		add_history(read_string);
		strncpy(cmd->full_cmd,read_string,MAX_READ_LEN-1);
		free(read_string);
		return TRUE;
	} else
		return FALSE;
}

