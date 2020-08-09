/*
Given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it palindrome.

Return the length of the maximum length awesome substring of s.

 

Example 1:

Input: s = "3242415"
Output: 5
Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
Example 2:

Input: s = "12345678"
Output: 1
Example 3:

Input: s = "213123"
Output: 6
Explanation: "213123" is the longest awesome substring, we can form the palindrome "231132" with some swaps.
Example 4:

Input: s = "00"
Output: 2
 

Constraints:

1 <= s.length <= 10^5
s consists only of digits.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int longestAwesome(string s) {
        int n = s.length();
        vector<int> dp(1025, n);
        dp[0] = -1;
        int curr = 0;
        int res = 0;

        for (int i = 0; i < n; i++) {
            curr ^= (1 << (s[i] - '0'));
            res = max(res, i - dp[curr]);  //for even palindrome
            for (int d = 0; d <= 9; d++)
                res = max(res, i - dp[curr ^ (1 << d)]);  //for odd palindrome
            dp[curr] = min(dp[curr], i);
        }

        return res;
    }
};

int main() {
    return 0;
}
