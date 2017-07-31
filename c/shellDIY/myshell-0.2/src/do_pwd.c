/*输入：无输入值
 *输出：如果错误：打印出错信息
 *              如果正确：打印当前路径信息
 *功能：打印当前路径信息
 *作者：李则良<lizeliang.linux@gmail.com>  
 *修改：
 */
#include"head.h"
void do_pwd(void)
{
	char *buf;
	if((buf=getcwd(NULL,0))) {
		printf("%s\n",buf);
		free(buf);
	} else if(errno==ERANGE)
		printf("buf too small\n");
	else
		printf("other error,errno=%d\n",errno);
	return ;
}
