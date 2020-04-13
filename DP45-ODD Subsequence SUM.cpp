/*
Given an array of integers A of size N. Find and return the number of subsequences of A having odd sum % 10^9 + 7. 
Input Format
The first argument given is the integer array A.
Output Format
Find and return the number of subsequences of A having odd sum % 1000000007.
Constraints
1 <= N <= 100000
-100000 <= A[i] <= 100000
For Example
Input 1:
    A = [-3, 8, 5]
Output 1:
    4
Explaination 1:
    Following are subsequences of A having odd sum:    (-3), (5), (-3, 8), (8, 5)

Input 2:
    A = [-4, -4, 1]
Output 2:
    4
Explaination 2:
    Following are subsequences of A having odd sum:    (-4, 1), (-4, 1), (1), (-4, -4, 1)
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

typedef long long ll;
ll MOD = 1e9 + 7;

int Solution::solve(vector<int> &A) {
    int n = A.size();
    vector<ll> cntEven(n + 1, 0), cntOdd(n + 1, 0);

    //dp[i][1]:= # of subsequences ending at i which are odd
    //dp[i][0]:= # of subsequences ending at i which are even

    //O+O=E
    //O+E=O
    //E+E=E
    //E+O=O

    for (int i = 1; i <= n; i++) {
        if (A[i - 1] % 2 == 0) {  //even
            //E+E=E
            //E+O=O
            cntEven[i] = (2 * cntEven[i - 1] + 1) % MOD;
            cntOdd[i] = (cntOdd[i - 1] + cntOdd[i - 1]) % MOD;
        } else {  //odd
            //O+O=E
            //O+E=O
            cntEven[i] = (cntEven[i - 1] + cntOdd[i - 1]) % MOD;
            cntOdd[i] = (cntOdd[i - 1] + cntEven[i - 1] + 1) % MOD;
        }
    }

    return cntOdd[n];
}

int main() {
    return 0;
}

/*
If we are at position i, and the number is ODD then the total number of subsequences with even sum would be
 countEVEN[i] = countEVEN[i-1] + countODD[i-1] 
 countODD[i] = countODD[i-1] + countEVEN[i-1] + 1
For countEVEN[i], the i-th number is not paired with any other subseuence (i.e. even subsequences till (i-1) position) + ith number is paired with all other odd subsequences till (i-1) position (odd+odd=even)
For countODD[i], the i-th number is not paired with any other subseuence(i.e. odd subsequences till (i-1) position) + ith number is paired with all other even subsequences till (i-1) position (odd+even=odd) + one subsequence with only 1 element i.e the ith number itself
If we are at position i, and the number is EVEN then the total number of subsequences with even sum would be
 countEVEN[i] = countEVEN[i-1] + countEVEN[i-1] + 1
 countODD[i] = countODD[i-1] + countODD[i-1]
For countEVEN[i], the i-th number is not paired with any other subseuence (i.e. even subsequences till (i-1) position) + i-th number is paired with all other even subsequences till (i-1) position (even+even=even) + one subsequence with only 1 element i.e the i-th number itself
For countODD[i], the i-th number is not paired with any other subseuence (i.e. odd subsequences till (i-1) position) + i-th number is paired with all other odd subsequences till (i-1) position (even+odd=odd)
*/