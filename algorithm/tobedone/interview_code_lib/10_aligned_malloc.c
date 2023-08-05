#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>

typedef uint16_t offset_t;

void *aligned_malloc(size_t required_bytes, size_t alignment)
{
    //1. need add a offset to malloc enough space
    int offset = alignment - 1;
    void *p_addr = NULL;

    /*2. malloc enough space: 
    1). original memory
    2). offset
    3). need extra space to save the difference between address and aligned_address
    */
    if((p_addr = (void *)malloc(required_bytes + offset + sizeof(offset_t))) == NULL)
    {
        return NULL;
    }

    //3. adjust the aligned_address, to align up the address to meet the alignment
    void *aligned_addr = (void *)(((size_t)p_addr + offset) & ~(offset));

    //4. save the difference
    *((size_t *)aligned_addr - 1) = (size_t)(aligned_addr - p_addr);

    //5. return aligned address
    return aligned_addr;
}


void aligned_free(void *ptr)
{
    assert(ptr);
    offset_t offset = *((offset_t *)ptr - 1);
    void *p = (void *)((int *)ptr - offset);
    free(p);
}