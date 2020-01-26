/*
There are n cities connected by m flights. Each fight starts from city u and arrives at v with a price w.

Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

typedef tuple<int, int, int> ti;
typedef pair<int, int> pi;

class Solution {
   public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<pi>> adj(n, vector<pi>());
        for (auto f : flights)
            adj[f[0]].emplace_back(f[1], f[2]);

        priority_queue<ti, vector<ti>, greater<ti>> pq;
        pq.emplace(0, src, K + 1);

        while (!pq.empty()) {
            auto [cost, u, stops] = pq.top();
            pq.pop();
            if (u == dst) return cost;
            if (!stops) continue;
            for (auto to : adj[u]) {
                auto [v, w] = to;
                pq.emplace(cost + w, v, stops - 1);
            }
        }

        return -1;
    }
};

int main() {
    return 0;
}
