#include "../../../include/common.h"
#include "../inc/test.h"



void test() {
    int arr[] = {100, 7, 98, 123, -12, 54};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("len = %d\n", len);
}


/*
    1. save very left one
    2. from 2nd element, if it's smaller than save, then continue the while loop
        else, break;
    3. from right element, if it's bigger than save, then continue the while loop
        else break;
    4. swap step 2 element with step 3 element
    5. if left == right, stop
    5. insert save to left
*/

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void insertSave(int *arr, int save, int pos) {
    //if(pos == 0) return;
    for(int i = 0; i < pos; i++) {
        arr[i] = arr[i + 1];
    }
    arr[pos] = arr[0];
}

int partition(int *arr, int left, int right) {
    int save = arr[left++];
    while(left < right) {
        while(arr[left] < save) {
            left++;
        }
        while(arr[right] > save) {
            right--;
        }
        if(left < right) {
            swap(arr + left, arr + right);
        }
    }
    insertSave(arr, save, left - 1);
}

void do_quicksort(int *arr, int left, int right) {
    //if (left >= right) return;
    int mid;

    while(left < right) {
        mid = partition(arr, left, right);
        do_quicksort(arr, 0, mid - 1);
        do_quicksort(arr, mid + 1, right);
    }
}

void quicksort() {
    printf("run quicksort!\n");

    int arr[] = {100, 7, 98, 123, -12, 54};
    int len = sizeof(arr) / sizeof(arr[0]);

    int start = 0;
    int end = len - 1;
    do_quicksort(arr, start, end);
}

void quicksort_2(int data) {
    printf("run quicksort! %d\n", data);
}