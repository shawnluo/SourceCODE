/*输入：cmd  ——包含要执行的命令的数据。
 *              cur_path ——当前所处的路径
 *输出：如果错误：打印错误信息
 *             如果正确：无输出
 *功能：切换到用户指定的目录。
 *             如果错误：中断执行，打印错误信息，并返回到上一级调用处
 *作者：李则良<lizeliang.linux@gmail.com> 
 *修改：
 */
#include"head.h"
void do_cd(Command *cmd, char *cur_path)
{
	char *dir;
	char *usr;
	char tmp[USER_NAME_LEN + 1];

	if (!(strlen(cmd->argv[0]))) {
		if (!(dir = getenv("HOME"))) {
			perror("getenv");
			return ;
		}
	} else {
		if (strcmp(cmd->argv[0], "-") == 0) {
			if (!(dir = getenv("OLDPWD"))) {
				perror("getenv");
				return ;
			}
			fprintf(stdout, "%s\n", dir);
		} else if ((strcmp(cmd->argv[0], "~") == 0) || (cmd->argv[0][0] == '~' && (cmd->argv[0][1] == ' ' || (cmd->argv[0][1] == '/' && cmd->argv[0][2] == '\0')))) {
			if (!(dir = getenv("HOME"))) {
				perror("getenv");
				return ;
			}
		} else if (cmd->argv[0][0] == '~') {
			if (cmd->argv[0][1] == '/' && cmd->argv[0][2] != ' ') {
				usr = cmd->argv[0] + 1;
				if (!(dir = getenv("HOME"))) {
					perror("getenv");
					return ;
				}
				strcpy(tmp, dir);
				strcat(tmp, usr);
				dir = tmp;
			} else {
				dir = cmd->argv[0] + 1;
				strcpy(tmp, strsep(&dir, "/"));
				struct passwd username, *other;
				other = &username;
				if (!(other = getpwnam(tmp))) {
					fprintf(stderr, "Myshell:%s No such file or Directory\n", tmp);
					return ;
				}
				strcpy(tmp, other->pw_dir);
				strcat(tmp, "/");
				strcat(tmp, dir == NULL ? "\0" : dir);
				dir = tmp;
			}
		} else {
			strcpy(tmp, cmd->argv[0]);
			dir = tmp;
		}
	}
	if ((setenv("OLDPWD", cur_path, 1)) == -1) {
		perror("setenv");
		return ;
	}
	if (chdir(dir) == -1)
		perror("myshell");

	if (!(getcwd(cur_path, CURRENT_PATH_LEN))) {
		perror("getcwd");
		return ;
	}
}

