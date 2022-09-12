#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stddef.h>

typedef struct data {
    int num;
    struct data *next;
} Data, *pData;

void showme();

#endif