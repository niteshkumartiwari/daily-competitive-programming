/*
       Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<C

Kathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.

 6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd

op= 2
*/

#include <bits/stdc++.h>
using namespace std;
string adj[1000];
int r, c;

int bfs() {
    vector<vector<int>> dp(r, vector<int>(c, INT_MAX));
    deque<pair<int, int>> q;
    q.push_front({0, 0});

    static int dr[] = {-1, 1, 0, 0};
    static int dc[] = {0, 0, 1, -1};

    dp[0][0] = 0;
    while (!q.empty()) {
        auto u = q.front();
        q.pop_front();
        for (int i = 0; i < 4; i++) {
            int vx = u.first + dr[i], vy = u.second + dc[i];

            if (vx < 0 || vx >= r || vy < 0 || vy >= c)
                continue;
            int add = 1;
            if (adj[vx][vy] == adj[u.first][u.second])
                add = 0;

            if (dp[vx][vy] > dp[u.first][u.second] + add) {
                dp[vx][vy] = dp[u.first][u.second] + add;

                if (add == 0)  //same level
                    q.push_front({vx, vy});
                else
                    q.push_back({vx, vy});
            }
        }
    }

    return dp[r - 1][c - 1];
}  //O(E+V)

int main() {
    int t, n;
    cin >> t;

    while (t--) {
        cin >> r >> c;
        for (int i = 0; i < r; i++)
            cin >> adj[i];

        cout << bfs() << endl;
    }
    return 0;
}