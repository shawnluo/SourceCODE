/*输入：cmd－包含要执行的命令的数据
 *current_path－shell命令解释器当前工作目录
 *输出：无
 *功能：初始化cmd变量。
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
void init_command (Command *cmd)
{
	int i;
	memset(cmd->full_cmd,'\0',MAX_READ_LEN);
	for(i=0;i<MAX_CMD_NUM;i++) {
		memset(cmd->cmd[i],'\0',MAX_CMD_LEN);
		memset(cmd->argv[i],'\0',PARAMETER_LEN);
		memset(cmd->cmd_path[i],'\0',CMD_PATH_LEN);
	}
	memset(cmd-> redirect_file_name,'\0',REDIRRECT_FILE_NAME);
	cmd->cmd_status=-1;
	cmd->is_input_redirect=0;
	cmd->is_output_redirect=0;
	cmd->is_pipeline=0;
	cmd->is_backgroud=0;
	cmd->next_command=NULL;
	return;
}/*getcwd(current_path,sizeof(current_path));*/
