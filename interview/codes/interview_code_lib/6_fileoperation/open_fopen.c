
#include <stdlib.h>
#include <stdio.h>


#include <unistd.h>

#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int  fd;
    FILE *file;
    char *s = "hello,world\n";

    if ((fd = open("test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
    {
        printf("Error open file\n");
        return -1;
    }
    if ((file = fopen("test2.txt", "w")) == NULL)
    {
        printf("Error Open File.\n");
        return -1;
    }
    printf("File has been Opened.\n");
	
//    sleep(15);
	
    if (write(fd, s, strlen(s)) < strlen(s))
    {
        printf("Write Error\n");

        return -1;
    }
    if (fwrite(s, sizeof(char), strlen(s), file) < strlen(s))
    {
        printf("Write Error in 2.\n");

        return -1;
    }
    printf("After write\n");

    sleep(15);
    printf("After sleep.\n");

    close(fd);
    return 0;
}
