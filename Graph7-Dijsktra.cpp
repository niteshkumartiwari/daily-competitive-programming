/*
Given a weighted undirected graph having A nodes and M weighted edges, and a source node C. You have to find an integer array D of size A such that:
=> D[i] : Shortest distance form the C node to node i. 
=> If node i is not reachable from C then -1.
Note:
There are no self-loops in the graph.
No multiple edges between two pair of vertices.
The graph may or may not be connected.
Nodes are numbered from 0 to A-1.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

//O(ELogV)- Single Source Multiple destination
#define pi pair<int, int>

vector<int> solve(int N, vector<vector<int>> B, int src) {
    vector<int> dist(N, INT_MAX / 10);
    vector<vector<pi>> adj(N, vector<pi>());

    for (int i = 0; i < B.size(); i++) {
        int u = B[i][0], v = B[i][1], wt = B[i][2];
        adj[u].push_back({wt, v});
        adj[v].push_back({wt, u});
    }

    dist[src] = 0;
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto u = pq.top();
        pq.pop();

        for (auto v : adj[u.second]) {
            if (dist[u.second] != INT_MAX && dist[v.second] > dist[u.second] + v.first) {
                dist[v.second] = dist[u.second] + v.first;
                pq.push(v);
            }
        }
    }

    for (int i = 0; i < N; i++)
        dist[i] = (dist[i] == INT_MAX / 10) ? -1 : dist[i];

    return dist;
}

int main() {
    return 0;
}
