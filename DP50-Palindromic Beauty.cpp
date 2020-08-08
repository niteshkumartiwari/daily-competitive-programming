/*
Problem Description

The palindromic beauty of a set of numbers is the number of palindromes in a set. A number is a palindrome that remains the same when its digits are reversed. The number should be considered without leading zeroes.

You have to solve q queries. You are given a list A of strings. List A contains numbers in string format. The ith query consists of numbers A[2*i] and A[2*i+1]. The answer to ith query is the palindromic beauty of set of numbers from A[2*i] to A[2*i+1]. Since the answer can be large, return it modulo 109 + 7.



Problem Constraints
2 <= |A| <= 400

|A| is even

1 <= |A[i]| <= 17

A[i] does not contain leading zeroes 



Input Format
The first line of input contains A- list of numbers in string format.



Output Format
Return  a vector of size q- ith of which contains the answer for ith query.



Example Input
Input 1:

  A = ["1", "5", "7", "12"]
Input 2:

  A = ["1", "100"]


Example Output
Output 1:

  [5, 4]
Output 2:

  18


Example Explanation
Explanation 1:

  In the first query, all numbers from 1 to 5 are palindromes.
  In the second query, 7, 8, 9 and 11 are palindromes.   
Explanation 2:

  Palindromes in the range are- 
  1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99
*/
#include <bits/stdc++.h>

#include <unordered_map>
#include <unordered_set>
using namespace std;
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 20005
#define ll long long
const int MOD = 1e9 + 7;
int dp[20][20][20];

/*----START CODING FROM HERE-------*/
int getAllPal(int length) {
    length = (length - 1) / 2;

    int result = 9;
    for (int i = 0; i < length; i++) {
        result = (result * 10) % MOD;
    }

    return result;
}

int go(string number) {
    int n = number.length();
    int len = n;

    if (len == 1) return (number[0] - '0');

    function<int(int, int, int)> go = [&](int i, int leftmost_lo, int leftmost_hi) {
        if (i == (ceil((len - 1) / 2)) + 1)
            return (leftmost_lo <= leftmost_hi) ? 1 : 0;

        int &memo = dp[i][leftmost_lo][leftmost_hi];
        if (memo != -1) return memo;

        int res = 0;
        int start = (i == 0) ? 1 : 0;  //to override leading zeros

        for (int d = start; d <= 9; d++) {
            int tmp_lo = leftmost_lo;
            int tmp_hi = leftmost_hi;

            if (d < (number[i] - '0') && i < tmp_lo) tmp_lo = i;
            if (d < (number[n - 1 - i] - '0') && (n - 1 - i) < tmp_lo) tmp_lo = (n - 1 - i);
            if (d > (number[i] - '0') && i < tmp_hi) tmp_hi = i;
            if (d > (number[n - 1 - i] - '0') && (n - 1 - i) < tmp_hi) tmp_hi = (n - 1 - i);

            res = (res + go(i + 1, tmp_lo, tmp_hi)) % MOD;
        }

        return memo = res;
    };

    int ans = 0;
    // for(len=1;len<=n;len++){
    // 	ans+=go(0,len+1,len+1);
    // }
    for (int i = 1; i < len; i++)
        ans = (ans + getAllPal(i)) % MOD;

    memset(dp, -1, sizeof dp);
    ans = (ans + go(0, n + 1, n + 1)) % MOD;

    return ans;
}

vector<int> solve(vector<string> &A) {
    vector<int> res;
    string s;

    for (int i = 0; i < A.size(); i += 2) {
        string l = A[i], r = A[i + 1];
        s = r;
        int resR = go(s);

        ll intL = stoll(l);
        s = to_string(intL - 1);
        int resL = go(s);

        res.push_back((resR - resL + MOD) % MOD);
    }

    return res;
}

int main() {
    vector<string> A{"85", "220"};

    vector<int> res = solve(A);

    for (int val : res)
        cout << val << " ";

    //cout<<go("85")<<endl;
    //cout<<go("220")<<endl;//88,99,101,,111,121,131,141,151,161,171,181,191,202,212

    return 0;
}