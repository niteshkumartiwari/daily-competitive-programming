/*
Given a matrix of integers A of size N x N, where A[i][j] represents the weight of directed edge from i to j (i ---> j). If i == j, A[i][j] = 0, and if there is no directed edge from vertex i to vertex j, A[i][j] = -1. Return a matrix B of size N x N where B[i][j] = shortest path from vertex i to vertex j. If there is no possible path from vertex i to vertex j
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

//O(V^3)- Mutiple Source Mutiple Path
vector<vector<int>> solve(vector<vector<int>> A) {
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX / 10));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != -1)
                dp[i][j] = A[i][j];
        }
    }

    for (int k = 0; k < n; k++) {  //for intermediate nodes
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = min(dp[i][j],
                               dp[i][k] + dp[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == INT_MAX / 10)
                dp[i][j] = -1;
        }
    }

    return dp;
}

int main() {
    return 0;
}
