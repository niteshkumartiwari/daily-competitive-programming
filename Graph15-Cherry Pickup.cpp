/*
In a N x N grid representing a field of cherries, each cell is one of three possible integers.

 

0 means the cell is empty, so you can pass through;
1 means the cell contains a cherry, that you can pick up and pass through;
-1 means the cell contains a thorn that blocks your way.
 

Your task is to collect maximum number of cherries possible by following the rules below:

 

Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
 

 

Example 1:

Input: grid =
[[0, 1, -1],
 [1, 0, -1],
 [1, 1,  1]]
Output: 5
Explanation: 
The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
 

Note:

grid is an N by N 2D array, with 1 <= N <= 50.
Each grid[i][j] is an integer in the set {-1, 0, 1}.
It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
    int dp[55][55][55];

   public:
    int cherryPickup(vector<vector<int>>& grid) {
        const int N = grid.size();
        function<int(int, int, int)> dfs = [&](int x, int y, int x1) {
            int y1 = x + y - x1;
            if (x < 0 || x >= N || y < 0 || y >= N || x1 < 0 || x1 >= N || y1 < 0 || y1 >= N || grid[x][y] == -1 || grid[x1][y1] == -1)
                return INT_MIN / 10;

            int& ans = dp[x][y][x1];

            if (ans != -1)
                return ans;

            if (x == N - 1 && y == N - 1 && x == x1 && y == y1)
                return grid[x][y];

            ans = grid[x][y] + grid[x1][y1];
            if (x == x1 && y == y1)
                ans -= grid[x][y];

            int a = dfs(x + 1, y, x1 + 1);  // DD
            int b = dfs(x, y + 1, x1);      // RR
            int c = dfs(x + 1, y, x1);      // DR
            int d = dfs(x, y + 1, x1 + 1);  // RD

            return ans = ans + max({a, b, c, d});
        };
        memset(dp, -1, sizeof dp);
        return dfs(0, 0, 0) < 0 ? 0 : dfs(0, 0, 0);
    }
};

int main() {
    return 0;
}
