/*
You are given a two-dimensional integer matrix containing 0s and 1s where 0 represents empty space and 1 represents a wall.

Return the minimum number cells that need to become walls such that there's no path from the top left cell to the bottom right cell. You cannot put walls on the top left cell and the bottom right cell. You are only allowed to travel adjacently (no diagonal moves allowed), and you can't leave the matrix.

Constraints

2 ≤ n, m ≤ 250 where n and m are the number of rows and columns in matrix
Example 1
Input
matrix = [
    [0, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 0, 0, 0]
]
Output
1
Explanation
We can put a wall on either matrix[2][0], matrix[2][1], matrix[1][0] or matrix[2][2].
*/

#include <bits/stdc++.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 100
#define ll long long
const int MOD = 1e9 + 7;
const int MAXBIT = 30;

/*----START CODING FROM HERE-------*/

int solve(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    //build-graph
    vector<vector<int>> adj(n * m, vector<int>());
    int dir[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int p1 = i * n + j;
            for (int k = 0; k < 4; k++) {
                int vx = i + dir[k][0], vy = j + dir[k][1];
                if (vx < 0 || vx >= m || vy < 0 || vy >= n || matrix[vx][vy]) continue;
                int p2 = vx * n + vy;

                adj[p1].push_back(p2);
            }
        }
    }

    cout << "built-graph" << endl;

    //vanilla-bfs (returns distance of all the nodes from the root)
    function<vector<int>(int)> bfs = [&](int root) {
        vector<int> dist(n * m, INT_MAX / 10);
        dist[root] = 0;
        queue<int> q;
        q.push(root);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == INT_MAX / 10) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        return dist;
    };

    auto dist1 = bfs(0);
    cout << "bfs1-done" << endl;
    auto dist2 = bfs(n * m - 1);
    cout << "bfs2-done" << endl;

    int d = dist1[n * m - 1];
    if (d == INT_MAX / 10) return 0;  // we can not reach dest

    vector<int> access(n * m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == 0 && j == 0) || (i == m - 1 && j == n - 1)) continue;

            int d1 = dist1[i * n + j];
            int d2 = dist2[i * n + j];

            if (d1 != INT_MAX / 10 && d2 != INT_MAX / 10 && d1 + d2 == d) {
                access[d1]++;
            }
        }
    }
    cout << "access-made-done" << endl;
    for (int i = 1; i < d; i++) {
        if (access[i] == 1) return 1;  //put a wall here
    }

    cout << "all-done" << endl;
    //we can always restrict src/dest with 2 walls!!
    return 2;
}

int main() {
    vector<vector<int>> matrix{
        {0, 0, 1},
        {0, 0, 0}};

    cout << solve(matrix);

    return 0;
}