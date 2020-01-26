/*
Given a string A, partition A such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of A.

Input 1:
    A = "aba"

Output 1:
    0

Explanation 1:
    "aba" is already a palindrome, so no cuts are needed.

Input 2:
    A = "aab"

Output 2:
    1
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int minCut(string A) {
    int n = A.size();
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) isPal[i][i] = true;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;

            if (A[i] == A[j] && len == 2)
                isPal[i][j] = true;
            else if (A[i] == A[j])
                isPal[i][j] = isPal[i + 1][j - 1];
        }
    }

    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        if (isPal[0][i]) {
            dp[i] = 0;
            continue;
        }
        dp[i] = i;
        for (int j = 0; j < i; j++) {
            if (isPal[j + 1][i] && dp[i] > dp[j] + 1)
                dp[i] = dp[j] + 1;
        }
    }

    return dp[n - 1];
}

int main() {
    return 0;
}
