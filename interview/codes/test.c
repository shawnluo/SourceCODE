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

#include <stdio.h>
#include <stdlib.h>


typedef uint16_t offset_t;
#define PTR_OFFSET_SZ sizeof(offset_t)

void* aligned_malloc(size_t required_bytes, size_t alignment)
{
    void *p_addr = NULL;
    void* aligned_addr = NULL;
    int offset = alignment - 1;
    
    // we also need about 2 bytes for storing offset to get to orig malloc address during aligned_free().
    uint32_t hdr_size = PTR_OFFSET_SZ + (alignment - 1);
    if((p_addr = (void * ) malloc(required_bytes + hdr_size)) == NULL)
    {
        return NULL;
    }

    // a) bit-shift to move address to aligned_addr
    //    Note that this operates on powers of two
    aligned_addr = (void * ) (((size_t)(p_addr) + offset) & ~(offset));
    
    #if 0
    //b) OR use modulo operator to get how much to move forward
    int move_forward = (alignment - ((size_t)p_addr % alignment));
    aligned_addr= (size_t)p_addr + move_forward;
    #endif

    // store 16-bit offset instead of a 32bit or 64 bit platform address.
    *((size_t *) aligned_addr - 1) = (size_t)(aligned_addr - p_addr);

    return aligned_addr;
}



void *align_ptr_free(void *ptr)
{
		void *base_addr = NULL;
		printf("%x %x\n", ptr, *((int *)ptr - 1));

		base_addr = (void *)(ptr - *((int *)ptr - 1));
		printf("ptr %x base_addr %x\n", ptr, base_addr);

		free(base_addr);
}

int main(void)
{
		void *ptr;
		//ptr = align_ptr_malloc(1024, 64);
        ptr = aligned_malloc(1024, 64);
		printf("ptr %x\n", ptr);
		align_ptr_free(ptr);

		return 0;
}