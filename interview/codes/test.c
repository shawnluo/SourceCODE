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


void *aligned_malloc(size_t required_bytes, size_t alignment)
{
    int offset = alignment - 1;
    void *p_addr = NULL;

    if((p_addr = (void *)malloc(required_bytes + offset + sizeof(uint16_t))) == NULL)
    {
        return NULL;
    }

    void *aligned_addr = (p_addr + offset) & ~(offset);
    *((int *)aligned_addr - 1) = aligned_addr - p_addr;

    return aligned_addr;
}

void aligned_free(void *ptr)
{
    assert(ptr);
    int offset = *((int *)ptr - 1);
    void *p = (void *)((int *)ptr - offset);
    free(p);
}