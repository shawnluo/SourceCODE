#ifndef MYSHELL_HEAD
#define MYSHELL_HEAD

#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<unistd.h>
#include <sys/mman.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include<sys/stat.h>
#include<readline/history.h>
#include<readline/readline.h>

typedef enum Boolean{FALSE,TRUE}boolean;

#define ERROR -1

#define MAX_READ_LEN 256 /*输入的最大字符的长度*/
#define CURRENT_PATH_LEN 256

#define MAX_CMD_NUM 5 /*组合命令的最大个数*/
#define MAX_CMD_LEN 15 /*命令的最大字符长度*/
#define CMD_PATH_LEN 80 /*命令路径的最大字符长度*/
#define PARAMETER_LEN 80 /*命令参数的长度*/
#define MAX_PARAMETER_NUM 20 /*命令的参数的最大个数*/
#define USER_NAME_LEN 20 /*用户名的最大长度*/
#define SHELL_PATH_NUM 20 /*shell环境变量目录的个数*/
#define REDIRRECT_FILE_NAME 80 /*重定向的文件名长度*/
#define INTERNAL_CMD_NUM 5 /*目前支持的内部命令的个数*/

typedef struct shell_command
{
	char    full_cmd[MAX_READ_LEN];               /*取得的命令行字符串*/
	char    cmd[MAX_CMD_NUM][MAX_CMD_LEN];         /*取得full_cmd中的命令*/
	int     cmd_status;  /*命令的种类(-1-错误命令,0-一般命令,1-含有输入/输出/管道/后台之一的命令),2-组合命令*/
	char    argv[MAX_CMD_NUM][PARAMETER_LEN];      /*argv[i]对应cmd[i]命令的参数*/
	char    cmd_path[MAX_CMD_NUM][CMD_PATH_LEN];   /*cmd_path[i]对应cmd[i]命令文件所在路径*/
	char    redirect_file_name[REDIRRECT_FILE_NAME];/*有重定向时的文件名*/
	boolean is_input_redirect;                   /*是否有输入重定向*/
	boolean is_output_redirect;                  /*是否有输出重定向*/
	boolean is_pipeline;                         /*是否有管道*/
	boolean is_backgroud;                        /*是否有后台运行*/
	struct  shell_command *next_command;          /*下一串命令*/
}Command;

/*
struct Internal_cmd
{
	char cmd[10];
	void (*do_cmd)(void *);
};
struct Internal_cmd internal_cmd[INTERNAL_CMD_NUM]={
		{"cd",do_cd},
		{"echo",do_echo},
		{"help",do_help},
		{"pwd",do_pwd},
		{"kill",do_kill}
		};
*/

#endif
