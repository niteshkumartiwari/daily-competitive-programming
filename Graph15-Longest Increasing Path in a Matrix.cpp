/*
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

Input: nums = 
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
] 
Output: 4 
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:

Input: nums = 
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
] 
Output: 4 
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int dir[][4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        function<int(int, int)> dfs = [&](int x, int y) {
            int& ans = dp[x][y];
            if (ans != -1) return ans;

            ans = 1;
            for (int i = 0; i < 4; i++) {
                int vx = x + dir[i][0], vy = y + dir[i][1];
                if (vx < 0 || vx >= n || vy < 0 || vy >= m || matrix[x][y] >= matrix[vx][vy]) continue;
                ans = max(ans, 1 + dfs(vx, vy));
            }

            return ans;
        };

        int maxLength = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                maxLength = max(maxLength, dfs(i, j));
            }
        }

        return maxLength;
    }
};

int main() {
    return 0;
}
