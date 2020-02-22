/*
Reziba gives you two numbers X and Y, he asks you a simple question based on them. Find the number of distinct sequences a1, a2, a3..., an where each ai >=1, such that:

gcd(a1, a2, a3...., an) = X

a1 + a2 + a3.... + an = Y

Both of the above rules should be satisfied by the sequence.
Find the number of sequences satisfying the above property MOD 109+7 Note: gcd here means the greatest common divisor Constraints:
1 <= X <= 10^9  
1 <= Y <= 10^9
Input:
X: gcd of sequence
Y: summation of sequence
Output:
Number of possible distinct positive sequences MOD 10^9+7
Example:
Input: 
X: 4
Y: 12

Output:
3

The sequences are: (4,4,4) , (4,8) , (8,4)

Input: 
X: 7
Y: 15

Output:
0

No sequences possible
*/
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

typedef long long ll;
ll MOD = 1e9 + 7;

ll fpow(ll n, ll k) {  //modular exponentiation (logn)
    ll r = 1;
    for (; k; k >>= 1) {
        if (k & 1)
            r = (r * n) % MOD;
        n = (n * n) % MOD;
    }

    return r;
}
int solve(int x, int y) {
    if (y % x != 0) return 0;
    y /= x;

    unordered_map<ll, ll> dp;
    dp[1] = 1;

    function<int(int)> go = [&](int N) {
        if (dp.count(N) != 0) return dp[N];

        ll ans = fpow(2, N - 1);
        vector<int> factors;
        for (int i = 1; i * i <= N; i++) {
            if (i == 1)
                factors.push_back(N);
            else if (N % i == 0) {
                factors.push_back(i);
                if (N / i != i)
                    factors.push_back(N / i);
            }
        }
        sort(factors.begin(), factors.end());

        for (int i = factors.size() - 1; i >= 0; i--) {
            ll tmp = N / factors[i];
            ll res = go(tmp);
            ans = (ans - res + MOD) % MOD;
        }

        return dp[N] = ans;
    };

    return go(y);
}

int main() {
    cout << solve(4, 12);
    return 0;
}