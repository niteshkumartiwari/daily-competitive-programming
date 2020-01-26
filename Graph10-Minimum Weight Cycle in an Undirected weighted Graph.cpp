/*
Given an integer A, representing number of vertices in a graph. Given a matrix of integers B of size N x 3 where N represents number of Edges in a Graph and Triplet (B[i][0], B[i][1], B[i][2]) implies there is an undirected edge between B[i][0] and B[i][1] and weight of that edge is B[i][2]. Find and return the weight of minimum weighted cycle and if there is no cycle return -1 instead. Note: Graph may contain multiple edges and self loops.

Input 1:
    A = 4
    B = [   [1 ,2 ,2]
            [2 ,3 ,3]
            [3 ,4 ,1]
            [4 ,1 ,4]
            [1 ,3 ,15]  ]
Output 1:
    10 

Explanation:
    Given graph forms 3 cycles
    1. 1 ---> 2 ---> 3 ---> 4 ---> 1 weight = 10
    2. 1 ---> 2 ---> 3 ---> 1 weight = 20
    3. 1 ---> 3---> 4 ---> 1 weight = 20
    so answer would be 10.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef pair<int, int> pi;

int minPath(list<pair<int, int>> adj[], int N, int src, int dest) {
    vector<int> dist(N + 1, INT_MAX / 10);
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()) {
        auto u = pq.top().second;
        pq.pop();

        if (u == dest) return dist[u];

        for (auto v : adj[u]) {
            if (dist[u] != INT_MAX / 10 && dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                pq.push({dist[v.first], v.first});
            }
        }
    }

    return -1;
}  //O(ElogV)

int solve(int A, vector<vector<int>>& B) {
    list<pair<int, int>> adj[A + 1];

    for (auto v : B) {
        adj[v[0]].push_back({v[1], v[2]});
        adj[v[1]].push_back({v[0], v[2]});
    }

    int res = INT_MAX;
    for (int i = 0; i < B.size(); i++) {
        int u = B[i][0], v = B[i][1], wt = B[i][2];

        //remove edge
        adj[u].remove({v, wt});
        adj[v].remove({u, wt});

        //find min-distance b/w u-v
        int minDist = minPath(adj, A, u, v);

        if (minDist != -1)
            res = min(res, minDist + wt);

        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    return res == INT_MAX ? -1 : res;
}  //O(E^2logV)

int main() {
    return 0;
}
