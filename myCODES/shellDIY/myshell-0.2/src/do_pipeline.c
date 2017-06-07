/*输入：cmd  ——包含要执行的命令的数据。
 *              cur_path ——当前所处的路径
 *输出：如果错误：打印错误信息
 *             如果正确：无输出
 *功能：切换到用户指定的目录。
 *            如果错误：中断执行，打印错误信息，并返回到上一级调用处
 *作者：李则良<lizeliang.linux@gmail.com>     
 *修改：      
 */
#include"head.h"
void do_pipeline(Command *cmd)
{
	int fd[2];
	pid_t pid=1;

	if(pipe(fd)<0) {
		perror("pipe");
		exit(1);
	}
	if((pid=fork())<0) {
		perror("fork");
		exit(1);
	}
	if(pid==0) {
		close(fd[1]);
		if(dup2(fd[0],STDIN_FILENO)==-1)
			exit(1);

		if((execl(cmd->cmd_path[1],cmd->cmd[1],cmd->argv[1],(char*)0))<0) {
			perror("execl");
			exit(1);
		}
	} else {
		close(1);
		close(fd[0]);
		if(dup2(fd[1],1)==-1)
			exit(1);

		if((execl(cmd->cmd_path[0],cmd->cmd[0],cmd->argv[0],(char*)0))<0) {
			perror("execl");
			exit(1);
		}

		wait(NULL);
	}

	return;
}

