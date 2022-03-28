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
    int offset = alignment - 1;
    void *p_addr = NULL;
    //need about 2 bytes for storing offset, to get to orig malloc address during aligned_free()
    if((p_addr = (void *)malloc(required_bytes + offset + sizeof(offset_t))) == NULL)
    {
        return NULL;
    }

    void *aligned_addr = (void *)(((size_t)p_addr + offset) & ~(offset));
    *((size_t *)aligned_addr - 1) = (size_t)(aligned_addr - p_addr);

    return aligned_addr;
}


void aligned_free(void *ptr)
{
    assert(ptr);
    offset_t offset = *((offset_t *)ptr - 1);
    void *p = (void *)((int *)ptr - offset);
    free(p);
}