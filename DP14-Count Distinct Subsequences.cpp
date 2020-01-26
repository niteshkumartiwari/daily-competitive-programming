/*
Constraints
1 <= N, M <= 100000
For Example
Input 1:
    A = "aba"
Output 1:
    6
Explanation 1:
    "a", "b", "ab", "ba", "aa", "aba"

Input 2:
    A = "abc"
Output 2:
    7
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll MOD = 1e9 + 7;

int solve(string A) {
    int n = A.size();
    vector<ll> dp(n + 1, 0);
    vector<ll> last(26, -1);

    dp[0] = 1;  //only one subsequence of empty string
    for (int i = 1; i <= n; i++) {
        dp[i] = (2 * dp[i - 1]) % MOD;
        if (last[A[i - 1] - 'a'] != -1)
            dp[i] = dp[i] - dp[last[A[i - 1] - 'a']];
        last[A[i - 1] - 'a'] = (i - 1);
    }

    return dp[n] - 1;
}

int main() {
    return 0;
}

/*
Let countSub(n) be count of subsequences of 
first n characters in input string. We can
recursively write it as below. 

countSub(n) = 2*Count(n-1) - Repetition

If current character, i.e., str[n-1] of str has
not appeared before, then 
   Repetition = 0

Else:
   Repetition  =  Count(m)
   Here m is index of previous occurrence of
   current character. We basically remove all
   counts ending with previous occurrence of
   current character.
How does this work?
If there are no repetitions, then count becomes double of count for n-1 because we get count(n-1) more subsequences by adding current character at the end of all subsequences possible with n-1 length.
If there repetitions, then we find count of all distinct subsequences ending with previous occurrence. This count can be obtained be recursively calling for index of previous occurrence.

Since above recurrence has overlapping subproblems, we can solve it using Dynamic Programming.
*/
