/*����:cmd������Ҫִ�е����������
 *    str����ʾ����ʾ��    
 *���:��
 *���ߣ�ţ��<niutao0602@gmail.com>
 *�޸�:
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

