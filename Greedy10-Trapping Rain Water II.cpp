/*
Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

 

Note:

Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

typedef pair<int, int> pi;

int trapRainWater(vector<vector<int>>& heightMap) {
    int n = heightMap.size();
    if (n == 0) return 0;
    int m = heightMap[0].size();

    priority_queue<pi, vector<pi>, greater<pi>> pq;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int i = 0; i < m; i++) {  //first and last row
        pq.emplace(heightMap[0][i], i);
        visited[0][i] = true;
        pq.emplace(heightMap[n - 1][i], (n - 1) * m + i);
        visited[n - 1][i] = true;
    }

    for (int i = 0; i < n; i++) {  //first and last col
        pq.emplace(heightMap[i][0], i * m);
        visited[i][0] = true;
        pq.emplace(heightMap[i][m - 1], i * m + m - 1);
        visited[i][m - 1] = true;
    }

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    int res = 0;
    while (!pq.empty()) {
        auto [height, cord] = pq.top();
        pq.pop();
        int r = cord / m, c = cord % m;

        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (r1 > 0 && r1 < n && c1 > 0 && c1 < m && !visited[r1][c1]) {
                visited[r1][c1] = true;
                res += max(0, height - heightMap[r1][c1]);
                pq.emplace(max(height, heightMap[r1][c1]), r1 * m + c1);
            }
        }
    }

    return res;
}

int main() {
    return 0;
}
