/*
Given a weighted undirected graph having A nodes, a source node C and destination node D. Find the shortest distance from C to D and if it is impossible to reach node D from C then return -1. You are expected to do it in Time Complexity of O(A + M). Note:
There are no self-loops in the graph.
No multiple edges between two pair of vertices.
The graph may or may not be connected.
Nodes are Numbered from 0 to A-1.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int solve(int A, vector<vector<int> > &B, int C, int D) {
    vector<bool> visited(3 * A + 1, false);
    vector<int> adj[3 * 10000 + 1];
    int dummy = A + 1;

    for (int i = 0; i < B.size(); i++) {
        int u = B[i][0], v = B[i][1], wt = B[i][2];

        if (wt == 1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        } else if (wt == 2) {  //u-----dummy-----v
            adj[u].push_back(dummy);
            adj[dummy].push_back(u);

            adj[dummy].push_back(v);
            adj[v].push_back(dummy);
            dummy++;
        }
    }

    int steps = 0;
    queue<int> q;
    q.push(C);

    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            int u = q.front();
            q.pop();
            visited[u] = true;

            if (u == D) return steps;

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        steps++;
    }

    return -1;
}  //O(E+V)

int main() {
    return 0;
}
