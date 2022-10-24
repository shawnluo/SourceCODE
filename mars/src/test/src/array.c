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
            printf("%f\n", arr[i]);
        }
    }
}