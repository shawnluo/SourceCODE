
/*
 *	mknod /dev/mycdev c 199 0
 *	Before we operate the "/dev/mycdev", we need mknod!
 */


#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#define BUFFERSIZE    200
int main(void)
{
    int  fp = 0;
    char str[BUFFERSIZE];
	memset(str, 0, 200);

    fp = open("/dev/mycdev", O_RDWR, S_IRUSR | S_IWUSR);
    if (!fp)
    {
        printf("Open device failed\n");
        return -1;
    }
	else
	{
		printf("Open device succeed\n");
	}
    write(fp, "Hello, my devices", strlen("Hello, my devices"));
	write(fp, "Hello", strlen("Hello"));
    lseek(fp, 0, 0);/*修改字符设备里字符数组的位置，将字符数据位置设到开始的位置，不然下面的read操作将读不到数据*/
    read(fp, str, BUFFERSIZE);
    printf("Read content: %s\n", str);
    close(fp);
}
