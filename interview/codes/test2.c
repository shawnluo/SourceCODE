/*信号量实现 生产者 消费者问题*/

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdint.h>

void *aligned_malloc(size_t required_bytes, size_t alignment)
{
    int offset = alignment - 1 + sizeof(void *);
    void *p1 = (void *)malloc(required_bytes + offset);

    if (p1 == NULL)
    {
        return NULL;
    }

    void **p2 = (void **)(((size_t)p1 + offset) & ~(alignment - 1));
    p2[-1] = p1;

    return p2;
}


void aligned_free(void *p2)
{
    void *p1 = ((void **)p2)[-1];

    free(p1);
}

int main()
{
    void *p[128];
    int i;

    for (i = 0; i < 128; ++i)
    {
        p[i] = aligned_malloc(i, 16);

        printf("%p\n", p[i]);
    }

    for (i = 0; i < 128; ++i)
    {
        aligned_free(p[i]);
    }

    return 0;
}