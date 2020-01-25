/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n, 0);  //longest valid parenthesis ending at i
        int currMax = 0;

        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i - 2 >= 0) ? dp[i - 2] + 2 : 2;
                    currMax = max(currMax, dp[i]);
                } else {
                    if (i - dp[i - 1] - 1 >= 0 && dp[i - dp[i - 1] - 1] == '(') {
                        dp[i] = dp[i - 1] + 2 + (i - dp[i - 1] - 2 >= 0) ? dp[i - dp[i - 1] - 2] : 0;
                        currMax = max(currMax, dp[i]);
                    }
                }
            }
        }

        return currMax;
    }
};

int main() {
    return 0;
}

/*
f s[i] is '(', set longest[i] to 0,because any string end with '(' cannot be a valid one.

Else if s[i] is ')'

     If s[i-1] is '(', longest[i] = longest[i-2] + 2

     Else if s[i-1] is ')' and s[i-longest[i-1]-1] == '(', longest[i] = longest[i-1] + 2 + longest[i-longest[i-1]-2]

For example, input "()(())", at i = 5, longest array is [0,2,0,0,2,0], longest[5] = longest[4] + 2 + longest[1] = 6.
*/
