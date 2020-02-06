/*
Q. Network Delay Time :=>
There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

Example 1:

Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2
 

Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {  //O(VE) can be done better with Dijsktra with ElogV
   public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<int> dist(N + 1, INT_MAX);
        dist[K] = 0;

        for (int i = 0; i < N; i++) {
            for (auto e : times) {
                int u = e[0], v = e[1], wt = e[2];

                if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
                    dist[v] = dist[u] + wt;
            }
        }

        int maxwait = 0;
        for (int i = 1; i <= N; i++)
            maxwait = max(maxwait, dist[i]);

        return maxwait == INT_MAX ? -1 : maxwait;
    }
};

int main() {
    return 0;
}
