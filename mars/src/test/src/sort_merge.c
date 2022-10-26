#include "../../../include/common.h"
#include "../inc/test.h"

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


//merge 2 array
int merge_array(int *arr1, int *arr2, int len1, int len2) {
    int i;
    int len = len1 + len2;

    while(len) {
        if(len1 >= 0 && arr1[len1] >= arr2[len2]) {
            tmp[len] = arr1[len1];
            len1--;
            len--;
        } else {
            tmp[len] = arr2[len2];
            len2--;
            len--;
        }
    }


    return 0;
}


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
void sort(int *arr, int L, int R) {
    int mid;
    if(L < R) {
        mid = (L + R) / 2;
        sort(arr, L, mid); 
        sort(arr, mid + 1, R);
        merge(arr, L, mid, R);
    } 
}