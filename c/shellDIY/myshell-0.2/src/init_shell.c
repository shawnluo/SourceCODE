/*输入： cmd－包含要执行的命令的数据，
 *      current_path－shell命令解释器当前工作目录，
 *	shell_path－shell的PATH环境变量。
 *输出：无
 *功能：初始化shell命令解释器工作环境。
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
extern void get_shell_path(char **shell_path);
extern void history_cmd_clew(void);
extern char help_path[CMD_PATH_LEN];

void init_shell(char *current_path,char **shell_path)
{
        if(getcwd(current_path,MAX_READ_LEN)==NULL) {
                perror("getcwd");
                exit(1);
        }
        strcpy(help_path,current_path);
        if(setenv("OLDPWD",getenv("HOME"),1)==-1) {
                perror("setenv");
                exit(ERROR);
        }
        get_shell_path(shell_path);
        history_cmd_clew();
        system("clear");
        return;
}

