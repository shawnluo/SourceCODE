

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>




int main(void)
{
    char *str = "goodaytodie!";
    int Is_uniq(str);
    return 0;
}

// aligned_malloc(1000, 128) will return a memory address
// that is a multiple of 128 and that points to memory of size 1000 bytes.
//offset_t is a uint16_t, supports up to 64KB alignment, a size which is already unlikely to be used for alignment.
typedef uint16_t offset_t;
#define PTR_OFFSET_SZ sizeof(offset_t)

void* aligned_malloc(size_t required_bytes, size_t alignment)
{
    int offset = alignment - 1;
    // we also need about 2 bytes for storing offset to get to orig malloc address during aligned_free().
    uint32_t hdr_size = PTR_OFFSET_SZ + (alignment - 1);
    if((p_addr = (void * ) malloc(required_bytes + hdr_size)) == NULL)
    {
        return NULL;
    }

    // a) bit-shift to move address to aligned_addr
    //    Note that this operates on powers of two
    void* aligned_addr = (void * ) (((size_t)(p_addr) + offset) & ~(offset));
    
    //b) OR use modulo operator to get how much to move forward
    int move_forward = (alignment - ((size_t)p_addr % alignment));
    void* aligned_addr= (size_t)p_addr + move_forward;

    // store 16-bit offset instead of a 32bit or 64 bit platform address.
    *((size_t *) aligned_addr - 1) = (size_t)(aligned_addr - p_addr);

    return aligned_addr;
}

void *alligned_malloc(size_t required_bytes, size_t alignment)
{
    int offset = alignment - 1;
    
}