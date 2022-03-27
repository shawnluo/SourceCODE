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
#define PTR_OFFSET_SZ sizeof(offset_t)

void *alignment_malloc(size_t required_bytes, size_t alignment)
{
    int offset = alignment - 1;
    //we also need about 2 bytes for storing offset to get to orig malloc address during aligned_free()
    uint32_t hdr_size = sizeof(offset_t) + (alignment - 1);
    if((p_addr = (void *)malloc(required_bytes + hdr_size)) == NULL)
    {
        return NULL;
    }

    void *aligned_addr = (void *)(((size_t)(p_addr) + offset) & ~(offset));

    *((size_t *)aligned_addr - 1) = (size_t)(aligned_addr - p_addr);

    return aligned_addr;
}

void *align_ptr_malloc(int size, int align_bytes)
{
    void *base_ptr = NULL;
    void *mem_ptr = NULL;
    int offset = align_bytes - 1;
    int hdr_size = offset + 1;  //header size
    base_ptr = malloc(size + offset);  //
    mem_ptr = (void *)(((int)(int *)base_ptr + hdr_size) & ~(align_bytes - 1));
    if(mem_ptr == base_ptr)
    {
        mem_ptr = base_ptr + align_bytes;
    }
    *((int *)mem_ptr - 1) = mem_ptr - base_ptr;

    return mem_ptr;
}

void aligned_free(void *ptr)
{
    assert(ptr);
    offset_t offset = *((offset_t *)ptr - 1);
    void *p = (void *)((int *)ptr - offset);
    free(p);
}

void Permu(char *pStr, char *pBegin)
{
    if(*pBegin == '\0') printf("%s\n", pStr);
    else{
        for(char *pCh = pBegin; *pCh != '\0'; ++pCh)
        {
            swap(pCh, pBegin);
            Permu(pStr, pBegn + 1);
            swap(pCh, pBegin);
        }
    }
}

void Permu(char *pStr, char *pBegin)
{
    if(*pBegin = '\0')
        printf("%s\n", pStr);
    else
    {
        for(char *p = pBegin; *p != '\0'; p++)
        {
            swap(pStr, pBegin);
            Permu(pStr, pBegin + 1);
            swap(pStr, pBegin);
        }
    }
}

typedef struct Data
{
    int id;
    struct Data *next;
}data, *pData;

#define size sizeof(data)

