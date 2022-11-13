#include "../../../include/common.h"
#include "../inc/test.h"



// 1.
//nums[] and val
//remove nums[i] which equals val
//don't change elements order in nums[]
//in place

/*solution 1: 
    using 2 array index to point to array:
    old points to the array,
    new points to the updated array.
    return the updated array length
*/

int rmv_val(int *nums, int len, int val, int target) {
    int old = 0, new = 0;

    while(old < len) {
        if(nums[old] == target) {
            old++;
        } else if(nums[old] != target) {
            nums[new] = nums[old];
            old++;
            new++;
        }
    }
    return (new - 1) >= 0 ? (new - 1) : new;
}


int sort_ascent(int *arr, int len) {
    int i;
    if(arr[0] >= 0) {
        for(i = 0; i < len; i++) {
            arr[i] = pow(i, 2);
            printf("%d\n", arr[i]);
        }
    }

    return 0;
}


//2.
//merge 2 array
int merge_array(int *arr1, int *arr2, int len1, int len2) {
    int len = 0;
    int l1 = 0;
    int l2 = 0;
    int tmp[len1 + len2];

    while(len < len1 + len2) {
        if(l1 <= len1 && l2 <= len2) {
            if(arr1[l1] <= arr2[l2]) {
                tmp[len] = arr1[len1];
                l1++;
                len++;
            } else {
                tmp[len] = arr2[len2];
                len2++;
                len++;
            }
        } else if(l1 <= len1) {
            for( ; l1 <= len1; len++, l1++) {
                tmp[len] = arr1[l1];
            }
        } else if(l2 <= len2) {
            for( ; l2 <= len2; l2++, len++) {
                tmp[len] = arr2[l2];
            }
        }
    }
    //print tmp
}


//3.
//merge:
//  arr[] L,       mid
//  arr[] mid + 1, R
void merge(int *arr, int L, int M, int R) {
    int len1 = M - L + 1;
    int len2 = R - (M - 1) + 1;
    int len_new = len1 + len2;
    int tmp[len_new];
    
    int len = len_new;
    int pos1 = L;
    int pos2 = M + 1;

    while(len) {
        if(arr[pos1] >= arr[pos2]) {
            tmp[len] = arr[pos1];
            len--;
            pos1--;
        } else {
            tmp[len] = arr[pos2];
            len--;
            pos2--;
        }
    }

    for(int i = 0; i < len_new; i++) {
        arr[L] = tmp[i];
    }
}

//sort_merge
void sort_merge(int *arr, int L, int R) {
    int mid;
    if(L < R) {
        mid = (L + R) / 2;
        sort_merge(arr, L, mid); 
        sort_merge(arr, mid + 1, R);
        merge(arr, L, mid, R);
    } 
}


//4.
//  --- bubble sorting

void bb(int *arr, int len) {
    int i, j;
    for(i = 0; i < len; i++) {
        for(j = 0; j < len - i; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}


//5.
//  --- quick sorting
int partition(int *arr, int left, int right) {
    int save = arr[left];

    while(left < right) {
        while(right > left && arr[right] >= save) {
            right--;
        }
        if(left < right) {
            arr[left++] = arr[right];
        }

        while(left <= right && arr[left] <= save) {
            left++;
        }
        if(left < right) {
            arr[right--] = arr[left];
        }
    }
    arr[left] = save;

    return left;
}

void sort_quick(int *arr, int L, int R) {
    if(L < R) {
        int pivot = partition(arr, L, R);
        sort_quick(arr, L, pivot - 1);
        sort_quick(arr, pivot + 1, R);
    }
}


//6. select
void sort_select(int *arr, int len) {
    int i, j;
    int min = 0;
    for(i = 0; i < len - 1; i++) {
        min = i;
        for(j = i + 1; j < len; j++) {
            if(arr[j] < min) {
                min = j;
            }
        }
        int tmp = arr[min];
        arr[min] = arr[j];
        arr[j] = tmp;
    }
}


//7. shell



//8. insert
//
int insert_sort(int *arr, int len) {
    if(arr == NULL) {
        return -1;
    }
    for(int i = 1; i < len; i++) {
        int save = arr[i];
        for(int j = i; j >= 0; j--) {
            if(arr[i] < arr[j]) {
                arr[j] = arr[j - 1];
            }
        }
        arr[i] = save;
    }
    return 0;
}