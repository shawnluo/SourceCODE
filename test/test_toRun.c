#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//solution1
// compare s[size] with s[0, size)
int cmp_end(char *s, int size) {
    for(int i = 0; i < size - 1; i++) {
        if(s[size] == s[i]) {
            return 0;
        }
    }
    return 1;
}

/*  using slide window
    maintain a array[start, end] is uniq, 
        if it's uniq,       then end++
        if it's not uniq,   then start++
*/
void longest(char *s) {
    int start, end;
    int size = strlen(s);
    int max = 0;
    char s_max[size];

    start = 0;
    end = 1;
    memset(s_max, 0, size);
    while(end < size) {
        while((end < size) && cmp_end(s + start, end - start)) {
            end++;
        }
        if((end < size) && (end - start > max)) {
            max = end - start;
            strncpy(s_max, s + start, end - start);
            s_max[end - start] = '\0';
        } else if((end == size) && (end - start + 1 > max)) {
            max = end - start + 1;
            strncpy(s_max, s + start, end - start + 1);
            s_max[end - start + 1] = '\0';
        }
        start++;
    }
    printf("%s\n", s_max);
}


/*solution2:
using hash table
*/
int hash[100] = {0};
int is_uniq(char *s, int start, int end) {
    int size = strlen(s);
    for(int i = 0; i < size; i++) {
        if(hash[s[]])
    }
}

//using hash table
void longest_1(char *s) {
    int size = strlen(s);
    int start = 0;
    int end = 0;
    int max = 0;
    char s_max[size];

    for(int i = 0; i < size; i++) {
        for(int j = 1; j < size; j++) {
            if(is_uniq(s, start, end)) {
                max = end - start;
            }
        }
    }
}

/**
 * intersection of 2 arrays: a1 = [1, 2, 3, 1]  a2 = [2, 3]   output: a[2, 3]
*/
void find_intersection(int a1[], int a2[], int size1, int size2){
    int hash[1000] = {0};
    for(i = 0; i < size1; i++) {
        hash[a1[i]]++;
    }
    for(i = 0, index = 0; i < size2; i++) {
        if(hash[a2[i]]) {
            hash[a2[i]]--;
            a[index++] = a2[i];
        }
    }
}


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
        sum = sum + pow(n % 10, 2);
        n = n / 10;
    }
    printf("sum = %d\n", sum);
}


void save_value(int i, int j, int k) {

}


void sort(int *a, int left, int right) {

}


int three_sum(int *a, int size, int target) {
    int pos = 0;
    int left = 1;
    int right = size - 1;
    int sum = 0;

    sort(a, 0, size - 1);
    for(int pos = 0; pos < size; pos++) {
        if(pos > 0 && a[pos] == a[pos - 1]) continue;

        while(left < right) {
            sum = a[pos] + a[left] + a[right];
            if(sum == target) {
                save_value(pos, left, right);
                while(left < right && a[left + 1] == a[left]) left++;
                while(left < right && a[right - 1] == a[right]) right--;
                left++, right--;
            }
            else if(sum < target) left++;
            else if(sum > target) right--;
        }
    }

    return 0;
}


int four_sum(int *a, int size, int target) {
    int pos1 = 0;
    int pos2 = 1;
    int left = 2;
    int right = size - 1;
    int sum = 0;

    sort(a, 0, size - 1);
    for(pos1 = 0; pos1 < size; pos1++) {
        for(pos2 = pos1 + 1; )
    }
}

int main(int argc, char *argv[]) {
    char *s = "abcacbe";
    longest(s);

    return 0;
}