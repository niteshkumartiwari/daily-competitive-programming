/*
Given N trees in a line with ith tree having height h[i]. You have to remove all the trees except the first one and the last one. The cost of removing ith tree is height[i - 1] * height[i] * height[i + 1]. As soon as the tree is removed it will not exist in the line anymore. You have to remove the trees in such a way that minimizes the cost. Constraints:
2 <= N <= 19
0 <= h[i] <= 400
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int solve(vector<int> &A) {
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    /*
        dp[i][j]=min coins cost to cut trees in [i,j+1]
        i-1,i,i+1......k-1,k,k+1......j-1,j,j+1
    */
    n -= 2;

    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k <= j; k++) {
                int val = 0;
                val += (dp[i][k - 1] != INT_MAX) ? dp[i][k - 1] : 0;
                val += (dp[k + 1][j] != INT_MAX) ? dp[k + 1][j] : 0;

                dp[i][j] = min(dp[i][j], val + A[i - 1] * A[k] * A[j + 1]);
            }
        }
    }

    return dp[1][n];
}

int main() {
    return 0;
}
