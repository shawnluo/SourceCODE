#include <stdio.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <string.h>  
  
/* first_test on 
 * first_test off 
 */   
int main(int argc ,char *argv[])  
  
{  
    int fd;  
    int val = 0;  
    fd = open("/dev/xxx",O_RDWR);  
    if (fd < 0)  
    {  
        printf("open error\n");  
    }  
      
    if (argc != 2)  
    {  
        printf("Usage:\n");  
        printf("%s <on|off>\n",argv[0]);  
        return 0;  
    }  
    if(strncmp(argv[1],"on",2) == 0)  
    {  
        val = 1;  
    }  
    else if (strncmp(argv[1],"off",3) == 0)  
    {  
        val = 0;  
    }   
    write(fd,&val,4);  
    return 0;  
}  

