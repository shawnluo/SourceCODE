#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
main()
{
    int fd;
    void *start;
    struct stat sb;
    fd = open("/dev/kmalloc_map",O_RDONLY);
    if (fd < 0)
    {
        printf("open fail\n");
    }
    start = mmap(NULL,100,PROT_READ,MAP_PRIVATE,fd,0);
    //start = mremap (start, 100, 1000, PROT_READ);
    if(start != MAP_FAILED) /*ÅÐ¶ÏÊÇ·ñÓ³Éä³É¹¦*/
    {
        printf("%s\n",start);
    }
    munmap(start,100); 
    close(fd);
}
