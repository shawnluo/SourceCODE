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
    int new_len = len1 + len2;

    //while()


    return 0;
}


//merge:
//  arr[] L,       mid
//  arr[] mid + 1, R
void merge(int *arr, int L, int mid, int R) {
    int tmp[R];
    int i = R;
    while(i )
}

//sort_merge
void sort(int *arr, int L, int R) {
    if(L > R) {
        return;
    } 
    int mid = (L + R) / 2;
    sort(arr, L, mid); 
    sort(arr, mid + 1, R);
    merge(arr, L, mid, R);
}