#include "../../../include/common.h"
#include "../inc/test.h"

void swap(int *x, int *y);


void showme(int *arr, int len) {
    for(int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void test() {
    int arr[] = {100, 200, 300, 400, 500};
    swap(arr + 1, arr + 2);
    showme(arr, 5);
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
        do_quicksort(arr, left, mid - 1);
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


// 
int binary_search_loop(int *arr, int target) {
    int left = 0;
    int len = sizeof(arr) / sizeof(arr[0]);
    int right = len - 1;
    int mid;

    while(left <= right){
        mid = (left + right) / 2;
        if(arr[mid] == target) {
            return mid;
        } else if(arr[mid] > target) {
            //search left
            right = mid - 1;
        } else if(arr[mid] < target) {
            //search right
            left = mid + 1;
        }

        if((left == right) && (arr[left] != target)) {
            printf("Can not find it!\n");
            return -1;
        }
    }
}


/// @brief 
/// @param arr 
/// @param left 
/// @param right 
/// @param target 
/// @return 
int binary_search_recursion(int *arr, int left, int right, int target) {
    if(left == right){
        if(arr[left] == target) {
            return left;
        } else {
            printf("Can not find it!\n");
            return -1;
        }
    }

    int mid = (left + right) / 2;
    if(target == arr[mid]) {
        return mid;
    } else if(target < arr[mid]) {
        right = mid - 1;
    } else {
        left = mid + 1;
    }
    binary_search_recursion(arr, left, right, target);
}


//1. find the 2 numbers which less than target

//2. 4 points, if they're square