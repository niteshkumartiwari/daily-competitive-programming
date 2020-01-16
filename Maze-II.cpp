/*
Given a matrix of integers A of size N x M describing a maze. The maze consists of empty locations and walls. 1 represents a wall in a matrix and 0 represents an empty location in a wall. There is a ball trapped in a maze. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction. Given two array of integers of size B and C of size 2 denoting the starting and destination position of the ball. Find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the starting position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.

Input 1:
    A = [   [0, 0, 1, 0, 0]
            [0, 0, 0, 0, 0]
            [0, 0, 0, 1, 0]
            [1, 1, 0, 1, 1]
            [0, 0, 0, 0, 0]   ] 
    B = [0, 4]
    C = [4, 4]
Output 1:
    12
    Shortest path to the destination: left -> down -> left -> down -> right -> down -> right
    The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.
*/
#include <bits/stdc++.h>
using namespace std;
//Approach 1 => BFS  O(N*M*max(N,M))

int solve(vector<vector<int>> &A, vector<int> &B, vector<int> &C) {
    int n = A.size(), m = A[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    dist[B[0]][B[1]] = 0;

    queue<pair<int, int>> q;
    q.push({B[0], B[1]});
    vector<vector<int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int vx = u.first + dir[i][0], vy = u.second + dir[i][1];
            int count = 0;
            while (vx >= 0 && vx < n && vy >= 0 && vy < m && A[vx][vy] == 0) {
                vx += dir[i][0];
                vy += dir[i][1];
                count++;
            }
            vx -= dir[i][0];
            vy -= dir[i][1];
            if (dist[vx][vy] > dist[u.first][u.second] + count) {
                dist[vx][vy] = dist[u.first][u.second] + count;
                q.push({vx, vy});
            }
        }
    }

    return dist[C[0]][C[1]] == INT_MAX ? -1 : dist[C[0]][C[1]];
}

//Approach 2 => Dijkstra O(N*M*log(N*M))
typedef pair<int, pair<int, int>> ppi;

int solve(vector<vector<int>> &A, vector<int> &B, vector<int> &C) {
    int n = A.size(), m = A[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    dist[B[0]][B[1]] = 0;

    priority_queue<ppi, vector<ppi>, greater<ppi>> pq;
    pq.push({0, {B[0], B[1]}});
    vector<vector<int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!pq.empty()) {
        auto u = pq.top();
        pq.pop();
        for (int i = 0; i < 4; i++) {
            int vx = u.second.first + dir[i][0], vy = u.second.second + dir[i][1];
            int count = 0;
            while (vx >= 0 && vx < n && vy >= 0 && vy < m && A[vx][vy] == 0) {
                vx += dir[i][0];
                vy += dir[i][1];
                count++;
            }
            vx -= dir[i][0];
            vy -= dir[i][1];
            if (dist[vx][vy] > dist[u.second.first][u.second.second] + count) {
                dist[vx][vy] = dist[u.second.first][u.second.second] + count;
                pq.push({dist[vx][vy], {vx, vy}});
            }
        }
    }

    return dist[C[0]][C[1]] == INT_MAX ? -1 : dist[C[0]][C[1]];
}

int main() {
    return 0;
}