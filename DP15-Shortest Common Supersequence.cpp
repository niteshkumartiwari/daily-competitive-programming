/*
Given two strings str1 and str2, find the shortest string that has both str1 and str2 as subsequences.
Examples :

Input:   str1 = "geek",  str2 = "eke"
Output: "geeke"

Input:   str1 = "AGGTAB",  str2 = "GXTXAYB"
Output:  "AGXGTXAYB"
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

string LCS(string A, string B) {
    int n = A.length(), m = B.length();
    vector<vector<string>> dp(n + 1, vector<string>(m + 1, ""));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + A[i - 1];
            else
                dp[i][j] = dp[i - 1][j].size() > dp[i][j - 1].size() ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    return dp[n][m];
}

string SCS(string str1, string str2) {
    int n = str1.length(), m = str2.length();
    string lcs = LCS(str1, str2);
    string res = "";
    int i = 0, j = 0;

    for (char c : lcs) {
        while (str1[i] != c)
            res += str1[i++];
        while (str2[j] != c)
            res += str2[j++];
        i++, j++;
        res += c;
    }

    return res + str1.substr(i) + str2.substr(j);
}

int main() {
    return 0;
}
