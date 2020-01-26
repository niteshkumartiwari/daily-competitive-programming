/*
Given an expression, A, with operands and operators (OR , AND , XOR), in how many ways can you evaluate the expression to true, by grouping in different ways? Operands are only true and false. Return the number of ways to evaluate the expression modulo 103 + 3. 
 Input Format:
The first and the only argument of input will contain a string, A.

The string A, may contain these characters:
    '|' will represent or operator 
    '&' will represent and operator
    '^' will represent xor operator
    'T' will represent true operand
    'F' will false
Output:
Return an integer, representing the number of ways to evaluate the string.
Constraints:
1 <= length(A) <= 150
Example:
Input 1:
    A = "T|F"

Output 1:
    1

Explanation 1:
    The only way to evaluate the expression is:
        => (T|F) = T 

Input 2:
    A = "T^T^F"

Output 2:
    0

Explanation 2:
    There is no way to evaluate A to a true statement.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define ll long long
ll MOD = 1e3 + 3;

ll dp[155][155][2];

int getRes(string A, int s, int e, bool me) {
    if (s > e) return 0;
    if (s == e) {
        if (me) return 'T' == A[s];
        return 'F' == A[s];
    }
    ll &ans = dp[s][e][me];
    if (ans != -1) return ans;

    for (int i = s + 1; i < e; i += 2) {
        ll e1t = getRes(A, s, i - 1, true);
        ll e1f = getRes(A, s, i - 1, false);
        ll e2t = getRes(A, i + 1, e, true);
        ll e2f = getRes(A, i + 1, e, false);

        if (A[i] == '^') {
            if (me)
                ans = (ans + (e1t * e2f) % MOD + (e1f * e2t) % MOD) % MOD;
            else
                ans = (ans + (e1t * e2t) % MOD + (e1f * e2f) % MOD) % MOD;
        }

        if (A[i] == '|') {
            if (me)
                ans = (ans + (e1t * e2f) % MOD + (e1t * e2t) % MOD + (e1f * e2t) % MOD) % MOD;
            else
                ans = (ans + (e1f * e2f) % MOD) % MOD;
        }

        if (A[i] == '&') {
            if (me)
                ans = (ans + (e1t * e2t) % MOD) % MOD;
            else
                ans = (ans + (e1f * e2f) % MOD + (e1f * e2t) % MOD + (e1t * e2f) % MOD) % MOD;
        }
    }
}

int cnttrue(string A) {
    int n = A.length();
    memset(dp, 0, sizeof dp);

    return getRes(A, 0, n - 1, true);
}

int main() {
    return 0;
}
