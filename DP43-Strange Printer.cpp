/*
There is a strange printer with the following two special requirements:

The printer can only print a sequence of the same character each time.
At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.
Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

Example 1:
Input: "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
Example 2:
Input: "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
Hint: Length of the given string will not exceed 100.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int strangePrinter(string s) {
        if (s.length() == 0) return 0;
        string tmp;
        tmp += s[0];
        for (int i = 1; i < s.length(); i++) {
            if (s[i] == s[i - 1]) continue;
            tmp += s[i];
        }
        s = tmp;
        int n = s.length();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(n, n));

        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
            if (i < n - 1)
                dp[i][i + 1] = (s[i] == s[i + 1]) ? 1 : 2;
        }

        for (int len = 2; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                dp[i][j] = len + 1;
                for (int k = i; k < j; k++) {
                    int temp = dp[i][k] + dp[k + 1][j];
                    dp[i][j] = min(dp[i][j],
                                   (s[k] == s[j]) ? temp - 1 : temp);
                }
            }
        }

        return dp[0][n - 1];
    }
};

int main() {
    return 0;
}
