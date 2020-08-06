/*
Nobita's teacher gave him some problems to solve.

He has to solve q queries. He is given a list A of strings. List A contains numbers in string format. The ith query consists of numbers A[2*i] and A[2*i+1]. The answer to ith query is the count from A[2*i] to A[2*i+1] whose decimal representation contains no more than 3 non-zero digits. Since the answer can be large, return it modulo 109 + 7.

Can you help him?



Problem Constraints
2 <= |A| <= 2*104

|A| is even

1 <= |A[i]| <= 18

A[i] does not contain leading zeroes 



Input Format
The first line of input contains A- list of numbers in string format.



Output Format
Return a vector of size q- ith of which contains the answer for ith query.



Example Input
Input 1:

  ["1", "10"]
Input 2:

  ["1109", "1115"]


Example Output
Output 1:

  10
Output 2:

  2


Example Explanation
Explanation 1:

  All numbers have less than or equal to 3 non-zero digits.
Explanation 2:

  The valid numbers are- 1109, 1110.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define ll long long
const int MOD = 1e9 + 7;
int dp[19][2][4];
int go(string s, int pos, int isFree, int nonZero) {
    int n = s.length();
    if (pos == n) return 1;

    int &memo = dp[pos][isFree][nonZero];
    if (memo != -1) return memo;

    int lim = (isFree == 1) ? 9 : s[pos] - '0';
    int ans = 0;

    for (int k = 0; k <= lim; k++) {
        if (k != 0 && nonZero == 3) continue;
        ans = (ans + go(s, pos + 1,
                        (k < (s[pos] - '0')) ? 1 : isFree,
                        nonZero + (k != 0))) %
              MOD;
    }

    return memo = ans;
}

vector<int> Solution::solve(vector<string> &A) {
    vector<int> res;
    string s;

    for (int i = 0; i < A.size(); i += 2) {
        string l = A[i], r = A[i + 1];
        s = r;
        memset(dp, -1, sizeof dp);
        int resR = go(s, 0, 0, 0);

        ll intL = stoll(l);
        s = to_string(intL - 1);
        memset(dp, -1, sizeof dp);
        int resL = go(s, 0, 0, 0);

        res.push_back(resR - resL);
    }

    return res;
}

int main() {
    return 0;
}
