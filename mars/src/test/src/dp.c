#include "../../../include/common.h"
#include "../inc/test.h"


// 1. 

int min(int x, int y) {
    return x >= y ? x : y;
}

int minCostClimbingStairs(int* cost, int costSize){
    int dp[costSize];
    dp[0] = cost[0];
    dp[1] = cost[1];
    
    for(int i = 2; i < costSize; i++) {
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    }

    //printf();
    return min(dp[costSize - 1], dp[costSize - 2]);
}

//2. robot path sum
/*
    m, n: given destiny
    x, y: current position
*/
int robot_find_path_sum(int m, int n, int x, int y) {
    int dp[m][n];
    return 0;
}