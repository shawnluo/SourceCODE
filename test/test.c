#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int is_happyTree(int num) {
    while(num > 0) {
        int bit = num % 10;
        printf("%d\n", num / 10);
        num = num / 10;
    }
    return 0;
}

void print_bits(int num) {
    //while(num) {
    if(num) {
        num = num / 10;
        print_bits(num);
        printf("%d\n", num % 10);
    }
    //printf("\n");
}

int get_sum(int n) {
    int sum = 0;
    while(n) {
        sum = sum + sqrt(n % 10);
        n = n / 10;
    }
    printf("sum = %d\n", sum);
}


int main(int argc, char *argv[]) {
    int num = 103;
    get_sum(num);

    return 0;
}