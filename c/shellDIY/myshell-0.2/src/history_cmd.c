/*
 *开启使用历史命令
 *user_home-当前用户的主目录
 *修改:
 */
#include"head.h"
extern char user_home[80];
void history_cmd_clew(void)
{
	char *p;
	p=getenv("HOME");
	strcpy(user_home,p);
	strcat(user_home,"/.myshell_history");
	using_history();
	stifle_history(500);
	write_history(user_home);
}

void history_exit(void)
{
	append_history(history_length, user_home);
	history_truncate_file(user_home, history_max_entries);
	if(remove(user_home)==-1) {
		perror("remove");
		exit(1);
	}
}

