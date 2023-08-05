#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;


class solution {
public:
    int fib(int N) {
        if(N <= 1)  return N;
        
        vector<int> dp(N + 1);
        dp[0] = 0;
        dp[1] = 1;

        for(int i = 2; i <= N; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[N];
    }

    vector<int> test() {
        vector<int> x;
        x.push_back(100);
        x.push_back(200);

        return x;
    }
};

int main(void) {
    solution mars;
    
    int ret = mars.fib(16);
    cout << ret << endl;

    vector<int> ret2 = mars.test();
    for (int x : ret2)
        cout << x << endl;

    return 0;
}