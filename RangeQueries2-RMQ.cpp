/*
sparse table method supports query operation in O(1) time with O(n Log n) preprocessing time and O(n Log n) space.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX = 500;

int dp[MAX][MAX];
//dp[i][j] denotes min values between A[i...j]

void preprocess(vector<int> A) {
    int n = A.size();

    //Initialize the intervals with length 1
    for (int i = 0; i < n; i++)
        dp[i][0] = i;

    //Compute values from the smaller to bigger intervals
    for (int j = 1; (1 << j) < n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            if (A[dp[i][j - 1]] < A[dp[i + (1 << (j - 1))][j - 1]])
                dp[i][j] = dp[i][j - 1];
            else
                dp[i][j] = dp[i + (1 << (j - 1))][j - 1];
        }
    }
}

int query(vector<int> A, int l, int r) {
    int n = A.size();
    int j = log2(r - l + 1);

    if (A[dp[l][j]] < A[dp[l + (r - l + 1) - (1 << j)][j]])
        return A[dp[l][j]];
    else
        return A[dp[l + (r - l + 1) - (1 << j)][j]];
}

int main() {
    vector<int> A{7, 2, 3, 0, 5, 10, 3, 12, 18};
    preprocess(A);
    vector<vector<int>> Q{{0, 4}, {4, 7}, {7, 8}};

    for (auto q : Q)
        cout << query(A, q[0], q[1]) << endl;

    return 0;
}
