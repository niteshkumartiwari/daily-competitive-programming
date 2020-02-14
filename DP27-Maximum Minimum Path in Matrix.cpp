/*
give a matrix,
Find all paths from top left to bottom right.
Find the minimum value of each path.
Find the maximum of these minimums.

{ 8 , 4 , 3 , 5 }

{ 6 , 5 , 9 , 8 }
This returns 5
All paths:
8-> 4-> 3-> 5-> 8 min: 3
8-> 4-> 3-> 9-> 8 min: 3
8-> 4-> 5-> 9-> 8 min: 5
8-> 6-> 5-> 9-> 8 min: 5
Result = Math.max (3,3,5,5,) = 5
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int maximumMinimumPath(vector<vector<int>> matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    dp[0][0] = matrix[0][0];
    for (int i = 1; i < n; i++)
        dp[i][0] = min(dp[i - 1][0], matrix[i][0]);

    for (int i = 1; i < m; i++)
        dp[0][i] = min(dp[0][i - 1], matrix[0][i]);

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = min(max(dp[i - 1][j], dp[i][j - 1]), matrix[i][j]);
        }
    }

    return dp[n - 1][m - 1];
}

int main() {
    return 0;
}
