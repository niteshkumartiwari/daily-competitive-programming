/*
A palindrome string is a string which reads the same forward and backward. If a palindrome string is of odd length l, then (l+1)/2th character (1 index based) is said to be the centre of the palindrome. You are given a string A. Return an array X of integers where X[i] = (number of odd length palindrome subsequence of A with A[i] as the centre) modulo 1000000007.

Example :
A : xyzx
Returns X as [1, 2, 2, 1]
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<int> solve(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    /*
        dp[i][j]:= # of palindromes from 0....i & j....n-1
        i & j are seperated by length len
        1. str[i]==str[j] 
            dp[i][j]=dp[i-1][j]+dp[i][j-1]
    */
    for (int len = n - 1; len >= 0; len--) {  //we are checking the corners
                                              //first and then coming inwards
        for (int i = 0; i + len < n; i++) {
            int j = i + len;

            if (i == 0 && j == n - 1) {
                if (s[i] == s[j])
                    dp[i][j] = 2;
                else
                    dp[i][j] = 1;
            } else {
                if (s[i] == s[j]) {
                    if (i - 1 >= 0)
                        dp[i][j] += dp[i - 1][j];
                    if (j + 1 < n)
                        dp[i][j] += dp[i][j + 1];
                    if (i - 1 < 0 || j + 1 >= n) {
                        // We have only 1 way that is to
                        // just pick these characters
                        dp[i][j] += 1;
                    }
                } else {
                    if (i - 1 >= 0)
                        dp[i][j] += dp[i - 1][j];
                    if (j + 1 < n)
                        dp[i][j] += dp[i][j + 1];
                    if (i - 1 >= 0 || j + 1 < n) {
                        dp[i][j] -= dp[i - 1][j + 1];
                    }
                }
            }
        }
    }

    vector<int> res(n, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0 || i == n - 1)
            res[i] = 1;
        else
            res[i] = dp[i - 1][i + 1];
    }

    return res;
}

int main() {
    return 0;
}
