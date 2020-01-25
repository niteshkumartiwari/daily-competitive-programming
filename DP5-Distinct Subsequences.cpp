/*
Given two sequences A, B, count number of unique ways in sequence A, to form a subsequence that is identical to the sequence B. Subsequence : A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int numDistinct(string A, string B) {
    int n = A.length();
    int m = B.length();

    if (n == 0 && m == 0)
        return 1;

    int dp[1000][1000];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i <= m; i++)
        dp[0][i] = 0;
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    return dp[n][m];
}

int main() {
    return 0;
}
