/*
We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.

We start at bus stop S (initially not on a bus), and we want to go to bus stop T. Travelling by buses only, what is the least number of buses we must take to reach our destination? Return -1 if it is not possible.

Example:
Input: 
routes = [[1, 2, 7], [3, 6, 7]]
S = 1
T = 6
Output: 2
Explanation: 
The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
Note:

1 <= routes.length <= 500.
1 <= routes[i].length <= 500.
0 <= routes[i][j] < 10 ^ 6.
*/
#include <bits/stdc++.h>
#include <unordered_map>
#define ll long long
using namespace std;

class Solution {
   public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        int n = routes.size();
        if (S == T) return 0;

        unordered_map<int, vector<int>> stop2bus;
        for (int i = 0; i < n; i++) {
            for (int stop : routes[i])
                stop2bus[stop].push_back(i);
        }

        queue<int> q;
        vector<bool> visited(n, false);
        q.push(S);
        int dist = 0;

        while (!q.empty()) {  //BFS on bus rather than stops since 10^6
            dist++;
            int size = q.size();
            while (size--) {
                int stop = q.front();
                q.pop();
                for (auto bus : stop2bus[stop]) {
                    if (visited[bus]) continue;
                    visited[bus] = true;
                    for (auto& st : routes[bus]) {
                        if (st == T) return dist;
                        q.push(st);
                    }
                }
            }
        }

        return -1;
    }
};

int main() {
    return 0;
}
