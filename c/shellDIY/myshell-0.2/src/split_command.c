/*输入：cmd--包含要执行的命令的数据
 *输出：如果命令为空，则返回FALSE,否则返回TRUE
 *功能：分割取得的命令
 *作者：牛涛<niutao0602@gmail.com>
 *修改:吴雨龙
 */
#include"head.h"
boolean split_one_command(Command *cmd);
void remove_space(char *string);

boolean split_command(Command *cmd)
{
	int i, j, cmd_len;
	char *p, strtok_str[] = ";";
	char command[MAX_READ_LEN];
	char child_cmd[MAX_CMD_NUM][MAX_READ_LEN];
	Command *L, *next_cmd = cmd;

	cmd_len = strlen(next_cmd->full_cmd);
	strcpy(command, cmd->full_cmd);

	for (i = 0;i < cmd_len;i++) {    /*修正输入的命令行字符串，给特殊字符前后加上空格*/
		if ((command[i] == '>' || command[i] == '<' || command[i] == '|' ||
			 command[i] == '&' || command[i] == ';') && (i < MAX_READ_LEN - 2)) {
			command[cmd_len + 2] = '\0';
			for (j = cmd_len;j > i + 1;j--) 
				command[j + 1] = command[j - 1];
			command[i + 2] = ' ';
			command[i + 1] = command[i];
			command[i] = ' ';
			i += 2;
			cmd_len += 2;
		}
	}

	if (strchr(command, ';') == NULL) {
		strcpy(next_cmd->full_cmd, command);
		if ((split_one_command(next_cmd)) == FALSE)
			return FALSE;
		return TRUE;
	} else {
		p = strtok( command, strtok_str);
		for (j = 0;p != NULL && j < MAX_CMD_NUM;j++) {
			strcpy(child_cmd[j], p);
			p = strtok(NULL, strtok_str);
		}
		for (i = 0;i < j;i++) {
			strcpy(next_cmd->full_cmd, child_cmd[i]);
			next_cmd->next_command = NULL;
			split_one_command(next_cmd);

			if (i < j - 1) { /*由于第一个已经申请好，所以要少申请一个*/
				L = (Command *)malloc(sizeof(Command));
				if (!L) {
					fprintf(stderr, "malloc error!...\n");
					exit(ERROR);
				}
				L->next_command = NULL;
				next_cmd->next_command = L;
				next_cmd = L;
			}
		}
	}
	return TRUE;
} /*boolean split_command(Command *cmd)*/

/*输入：cmd--包含要执行的命令的数据
 *输出：如果命令为空，则返回FALSE,否则返回TRUE
 *功能：分割单个的命令
 *修改:
 */
boolean split_one_command(Command *cmd)
{
	int i, len;
	int k = 0, cmd_status = 0;
	char strtok_str[] = " ";
	char command[MAX_PARAMETER_NUM][MAX_CMD_LEN];
	char *p = cmd->full_cmd;
	char path[MAX_READ_LEN];

	if ((len = strlen(cmd->full_cmd)) == 0) {
		cmd->cmd_status = -1;
		return TRUE;
	}

	remove_space(p);
	strcpy(path, p);

	if (!(strchr(cmd->full_cmd, '>') || strchr(cmd->full_cmd, '<') ||
		  strchr(cmd->full_cmd, '|') || strchr(cmd->full_cmd, '&'))) {
		/*如果没有输入输出重定向，管道，后台，则做相应简单处理，返回*/
		strcpy(cmd->cmd[0], strsep(&p, strtok_str));
		if (p) strcpy(cmd->argv[0], p);
		cmd->cmd_status = 0;
		return TRUE;
	}
	memset(command, '\0', MAX_PARAMETER_NUM*MAX_CMD_LEN);
	p = strtok( path, strtok_str);
	for (i = 0;p != NULL && k < MAX_PARAMETER_NUM;i++) {
		strcpy(command[k++], p);
		p = strtok(NULL, strtok_str);
	}

	strcpy(cmd->cmd[0], command[0]);
	for (i = 1;command[i][0] != '\0' && i < k;i++) { /*start for*/
		if (command[i][0] == '<' || command[i][0] == '>' || command[i][0] == '|' || command[i][0] == '&') {
			cmd_status += 1;
			if (cmd_status == 2) {
				cmd->cmd_status = 2;
				return TRUE;
			}
			if (command[i + 1][0] == '\0' && command[i][0] != '&') {

				cmd->cmd_status = -1;
				return FALSE;
			}
			switch (command[i][0]) { /*start switch*/
			case '>':
			case '<':
				if (command[i][0] == '>')
					cmd->is_output_redirect = 1;
				else
					cmd->is_input_redirect = 1;
				strcpy(cmd->redirect_file_name, command[i + 1]);
				i++;
				continue;
			case '|':
			case '&':
				if (command[i][0] == '|')
					cmd->is_pipeline = 1;
				else
					cmd->is_backgroud = 1;
				strcpy(cmd->cmd[1], command[i + 1]);
				for (i += 2;command[i][0] != '\0' && i < k;i++) {
					if (command[i][0] != '<' && command[i][0] != '>' && command[i][0] != '|' && command[i][0] != '&') {
						strcat(cmd->argv[1], command[i]);
						strcat(cmd->argv[1], " ");
					} else
						break;
				}

				break;
			} /*end switch*/
		}
		strcat(cmd->argv[i - 1], command[i]);
		strcat(cmd->argv[i - 1], " ");
	} /*end for*/
	cmd->cmd_status = cmd_status;

	return TRUE;

} /*boolean split_one_command(Command *cmd)*/

/*输入：string－要修正的字符串
 *输出：无
 *功能：去掉string两端的空格
 *修改:
 */
void remove_space(char *string)
{
	char *p;
	int i = 0, j;
	int len;
	len = strlen(string);
	p = string + len;
	while (p--)
		if (*p == ' ')
			*p = '\0';
		else
			break;
	p = string;
	do {
		if (*p != ' ')
			break;
		i++;
	} while (p++);
	len -= i;
	for (j = 0;len >= 0;j++, len--)
		string[j] = string[j + i];
	return ;

}

/*输入：cmd--包含要执行的命令的数据
 *输出：无
 *功能：修正命令的参数
 *修改:
 */
void correction_cmd(Command *cmd)
{
	Command *L = cmd;
	int i;
	while (L != NULL) {
		for (i = 0;L->argv[i][0] != '\0' && i < MAX_CMD_NUM;i++)
			remove_space(L->argv[i]);
		L = L->next_command;
	}
	return ;
}
