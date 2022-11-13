//#include "../../../include/common.h"
//#include "../inc/test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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


//find the longest no repeat charater substring
void test() {
    char *arr = "abcabcdefgh";
    int n = strlen(arr);
    int max_len = 0;
    int cur_len = 0;
    char longest_str[n];
    int hash[255] = {0};
    int y = 0;

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(hash[arr[j]] == 0) {
                hash[arr[j]] = 1;
                cur_len++;
            } else {
                memset(hash, 0, 255);
                if(cur_len > max_len) {
                    max_len = cur_len;
                    //copy str[i] to str[j - 1] to longest_str
                    strncpy(longest_str, arr + i, cur_len);
                    longest_str[cur_len] = '\0';

                    printf("longest_str: %s\n", longest_str);
                    cur_len = 0;
                }
            }
        }
    }
//    printf("%s\n", longest_str);
}



int main(int argc, int *argv[]) {
    #if 0
    test();
    #else
    char *str = "abcde";
    char newStr[10] = "xxxxxx";

    //newStr[0] = str[0];
    //newStr[1] = str[1];
    //newStr[2] = '\0';

    strncpy(newStr, str + 1, 3);
    newStr[3] = '\0';

    printf("%s\n", newStr);
    #endif

    return 0;
}