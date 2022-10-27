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
            printf("%d, ", arr[i]);
            arr[i] = pow(arr[i] * 1.0, 2);
            printf("%f\n", arr[i]);
        }
    }
}


/*2. binary search
    in sorted array, find the target
*/
int b_search(int *arr, int start, int end, int target) {
    if(start <= end) {
        int mid = (end - start + 1) / 2;
        if(arr[mid] == target) {
            return mid;
        } else if(arr[mid] > target) {
            b_search(arr, start, mid - 1, target);
        } else if(arr[mid] < target) {
            b_search(arr, mid + 1, end, target);
        }
    }

    printf("can not find it!\n");
    return -1;
}