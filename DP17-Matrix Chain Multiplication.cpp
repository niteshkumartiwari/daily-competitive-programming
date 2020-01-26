/*
Given an array of integers A representing chain of 2-D matices such that the dimensions of ith matrix is A[i-1] x A[i]. Find the most efficient way to multiply these matrices together. The problem is not actually to perform the multiplications, but merely to decide in which order to perform the multiplications. Return the minimum number of multiplications needed to multiply the chain

Input 1:
    A = [40, 20, 30, 10, 30]
Output 1:
    26000
    Explanation 1:
        Dimensions of A1 = 40 x 20
        Dimensions of A2 = 20 x 30
        Dimensions of A3 = 30 x 10
        Dimensions of A4 = 10 x 30
        First, multiply A2 and A3 ,cost = 20*30*10 = 6000
        Second, multilpy A1 and (Matrix obtained after multilying A2 and A3) =  40 * 20 * 10 = 8000
        Third, multiply (Matrix obtained after multiplying A1, A2 and A3) and A4 =  40 * 10 * 30 = 12000
        Total Cost = 12000 + 8000 + 6000 =26000

Input 2:
    A = [10, 20, 30] 
Output 2:
    6000
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int solve(vector<int> &A) {
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    /* dp   [i,j] = Minimum number of scalar  
    multiplications needed to compute the 
    matrix A[i]A[i+1]...A[j] = A[i..j] where 
    dimension of A[i] is p[i-1] x p[i] */

    for (int len = 2; len < n; len++) {
        for (int i = 0; i < i - len + 1; i++) {
            int j = i + len - 1;

            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + A[i - 1] * A[k] * A[j]);
        }
    }

    return dp[1][n - 1];
}

int main() {
    return 0;
}
