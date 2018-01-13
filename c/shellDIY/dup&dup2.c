#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 int main(void)
 {
     int fd, save_fd;
     char msg[] = "This is a test of dup() & dup2()\n";
     int test;
	 
     fd = open("somefile", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
     if(fd<0) 
	 {
         perror("open");
         exit(1);
     }
	 
     save_fd = dup(STDOUT_FILENO);                        //���к�save_fdָ��STDOUT����FILENO����save_fdָ���׼���
     printf("save_fd=%d\n",save_fd);                             //������
     
     test=dup2(fd, STDOUT_FILENO);                         //���к�STDOUT_FILENOָ��fd��ָ����ļ�����STDOUT_FILENOָ��somefile
     printf("dup2_1=%d\n",test);                                   //������ ��ʱ�ı�׼�������ָ����ʾ������˸öβ��Խ�д��somefile�ļ���
     close(fd);
	 
     write(STDOUT_FILENO, msg, strlen(msg));           //��ʱSTDOUT_FILENO��ָ�����somefile�ļ������Ǳ�׼�����,��˸öν�
                                                                              //д��somefile�ļ���
     test=dup2(save_fd, STDOUT_FILENO);                 //���к�STDOUT_FILENOָ��save_fd��ָ����ļ�,����׼�����
     printf("dup2_2=%d\n",test);                                  //������ ��ʱ��׼���������ָ����ʾ������˸öβ��Խ�д����ʾ��
     write(STDOUT_FILENO, msg, strlen(msg));           //��ʱSTDOUT_FILENO��ָ��ı�ر�׼������öν�д����ʾ��
     close(save_fd);
     return 0;
 }


