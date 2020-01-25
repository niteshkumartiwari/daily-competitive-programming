/*
Given an integer A, how many structurally unique BST's (binary search trees) exist that can store values 1...A
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int solve(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= n; i++) {           //calculating for i
        for (int j = 1; j <= i; j++) {       //making j as root one by one
            dp[i] += dp[j - 1] * dp[i - j];  //ways(left)+ways(right)
        }
    }

    return dp[n];
}

int main() {
    return 0;
}

/*
For all possible values of i, consider i as root, then [1….i-1] numbers will fall in the left subtree and [i+1….n] numbers will fall in the right subtree. So, add (i-1)*(n-i) to the answer. The summation of the products will be the answer to the number of unique BST.
*/
