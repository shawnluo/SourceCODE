#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// sqrt( (x1 - x2)^2 + (y1 - y2)^2 )
int cal_dis(int *arr1, int *arr2, int len)
{
    assert(arr1);
    assert(arr2);
    // x, y;
    return sqrt( (arr1[0] - arr2[0])^2 + (arr1[1] - arr2[1])^2 );
}

int isSq(int arr[4][2], int row, int col)
{
    //find 
    int i, j;
    int result[6] = {0};

    result[0] = cal_dis(arr[0], arr[1], 2);
    result[1] = cal_dis(arr[1], arr[2], 2);
    result[2] = cal_dis(arr[2], arr[3], 2);
    result[3] = cal_dis(arr[3], arr[4], 2);
    
    result[4] = cal_dis(arr[0], arr[2], 2);
    result[5] = cal_dis(arr[1], arr[3], 2);
    
    //int key1 = result[0];
    int save1 = 0;
    int save2 = 0;
    int cnt1 = 0;
    int cnt2 = 0;
    
    //result[0] = 10
    //result[1] = 20
    //result[3] = 10
    //result[4] = 10
    //result[5] = 10
    //result[6] = 10
    
    save1 = result[0];
    
    for(i = 0; i < 6; i++)
    {
        if(save1 != result[i])
        {
            save2 = result[i];
            break;
        }
    }
    
    if(i == 6)  return 1;    
    
    for(i = 0; i < 6; i++)
    {
        if(result[i] == save1)    cnt1++;
        else if(result[i] == save2)        
        {
            cnt2++;
        }
        else
        {
            return -1;      //not sq
        }
    }
    
    if(((cnt1 == 4) && (cnt2 == 2)) || ((cnt1 == 2) && (cnt2 ==4)))
        return 1;
    else
        return 0;    
}

/*

- negative numbers
- all same point

*/
int main() {
    int arr[4][2] = {{},{},{},{}};
    int len1, len2;
        
    
    int val = isSq(arr, 4, 2);

    return 0;
}


// 0, 0 -   1, 1
// 1, 0 -   0, 1

//    0, 2 
//1, 0   
    2, 3
//
//  3, 1