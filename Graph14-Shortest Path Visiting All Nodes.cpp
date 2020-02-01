/*
An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.

graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.

Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

 

Example 1:

Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]
Example 2:

Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
 

Note:

1 <= graph.length <= 12
0 <= graph[i].length < graph.length
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> dp(n, vector<int>(1 << n, INT_MAX));
        //dp[i][mask] represent distance from i through set bits of mask

        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            dp[i][1 << i] = 0;
            q.push({i, 1 << i});
        }

        while (!q.empty()) {
            auto [u, mask] = q.front();
            q.pop();

            for (auto v : graph[u]) {
                int nextMask = mask | 1 << v;
                if (dp[v][nextMask] > dp[u][mask] + 1) {
                    dp[v][nextMask] = dp[u][mask] + 1;
                    q.push({v, nextMask});
                }
            }
        }

        int res = INT_MAX;
        for (int i = 0; i < n; i++)
            res = min(res, dp[i][(1 << n) - 1]);

        return res;
    }
};

int main() {
    return 0;
}
