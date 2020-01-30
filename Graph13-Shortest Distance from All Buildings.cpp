/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:
Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
Example:
Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):
1
2
3
4
5


1 - 0 - 2 - 0 - 1


|   |   |   |   |


0 - 0 - 0 - 0 - 0


|   |   |   |   |


0 - 0 - 1 - 0 - 0

The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
Return 7.
Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int shortestDistance(vector<vector<int>> grid) {  //O(N^2*M^2)
    int n = grid.size(), m = grid[0].size();
    int totBuildings = 0;

    vector<vector<int>> dist(n, vector<int>(m, 0));
    vector<vector<int>> hit(n, vector<int>(m, 0));
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    function<bool(int, int)> BFS = [&](int x, int y) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pair<int, int>> q;
        q.emplace(x, y);
        visited[x][y] = true;
        int steps = 0, buildings = 1;

        while (!q.empty()) {
            ++steps;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto u = q.front();
                q.pop();

                for (auto d : dir) {
                    int vx = u.first + d[0], vy = u.second + d[1];

                    if (vx < 0 || vx >= n || vy < 0 || vy >= m || grid[vx][vy] == 2 || visited[vx][vy]) continue;

                    visited[vx][vy] = true;
                    if (grid[vx][vy] == 0) {  //grass
                        dist[vx][vy] += steps;
                        hit[vx][vy]++;
                        q.emplace(vx, vy);
                    } else if (grid[vx][vy] == 1) {  //building
                        buildings++;
                    }
                }
            }
        }

        return buildings == totBuildings;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) totBuildings++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {  //isBuilding()
                if (!BFS(i, j))
                    return -1;
            }
        }
    }

    int res = INT_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0 && hit[i][j] == totBuildings) {
                res = min(res, dist[i][j]);
            }
        }
    }

    return (res == INT_MAX) ? -1 : res;
}

int main() {
    vector<vector<int>> grid{
        {1, 0, 2, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0}};

    cout << shortestDistance(grid);

    return 0;
}
