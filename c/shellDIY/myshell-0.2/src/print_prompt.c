/*输入：current_path－－由getcwd()函数取得的当前路径
 *输出：无
 *功能：打印命令提示符。
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
void print_prompt(char *current_path,char print_str[])
{
	char user_name[USER_NAME_LEN];
	char *p,strtok_str[]= "/";
	char path[CMD_PATH_LEN];
	char path_string[CMD_PATH_LEN];
	int path_len,len=0;
	int i;

	strcpy(user_name,getlogin());
	strcpy(path,current_path);

	for(path_len=0,i=0;i<strlen(path);i++)
		if(path[i]=='/') path_len++;

	strcpy(path_string,"[");
	strcat(path_string,user_name);
	strcpy(path,current_path);

	if(path_len>5) /*如果当前路径深度大于5级，则只打印开始目录和作后四个目录，缩短提示符长度*/
	{
		p = strtok( path, strtok_str );
		strcat(path_string,":/");
		strcat(path_string,p);
		strcat(path_string,".../");

		for(len=0;p!=NULL&&(len<path_len);len++) {
			p=strtok(NULL,strtok_str);;
			if(p!=NULL&&(len>path_len-4)) {
				strcat(path_string,p);
				strcat(path_string,"/");
			}
		}
	} else {
		strcat(path_string,":");
		strcat(path_string,path);
	}

	strncat(path_string,"] ",2);
	strcpy(print_str,path_string);
	return ;
}/* void print_prompt(char *current_path) */
