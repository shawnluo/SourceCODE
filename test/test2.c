#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

void test(int n[]) {
    printf("test: %d\n", sizeof(n));
}

int main(void) {
    int n[10];

    test(n);
    
    printf("x = %d\n", sizeof(n));

    return 0;
}