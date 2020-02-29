/*
Given an array of integers A of size N. Value of a subarray is defined as BITWISE OR of all elements in it. Return the sum of Value of all subarrays of A % 10^9 + 7. 
Input Format
The first argument given is the integer array A.
Output Format
Return the sum of Value of all subarrays of A % 10^9 + 7.
Constraints
1 <= N <= 10^5
1 <= A[i] <= 10^8
For Example
Input 1:
    A = [1, 2, 3, 4, 5]
Output 1:
    71
Explaination 1:
    Value( [ 1 ] ) =    1
    Value( [ 1,2 ] ) =    3
    Value( [ 1,2,3 ] ) =    3
    Value( [ 1,2,3,4 ] ) =    7
    Value( [ 1,2,3,4,5 ] ) =    7
    Value( [ 2 ] ) =    2
    Value( [ 2,3 ] ) =    3
    Value( [ 2,3,4 ] ) =    7
    Value( [ 2,3,4,5 ] ) =    7
    Value( [ 3 ] ) =    3
    Value( [ 3,4 ] ) =    7
    Value( [ 3,4,5 ] ) =    7
    Value( [ 4 ] ) =    4
    Value( [ 4,5 ] ) =    5
    Value( [ 5 ] ) =    5
    Sum of all these values = 71

Input 2:
    A = [7, 8, 9, 10]
Output 2:
    110
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

int solve(vector<int> &A) {
    ll n = A.size();
    ll reqSubArr = 0;

    for (int j = 0; j < 32; j++) {
        int sum = 0, i = 0;
        ll totSubArrays = ((n * (n + 1)) % MOD) / 2;
        while (i < n) {
            //finding 0s window
            while (i < n && (A[i] >> j & 1) == 1) i++;
            if (i == n) continue;
            int ws = i;  //start
            while (i < n && (A[i] >> j & 1) == 0) i++;
            ll k = i - ws;  //size

            ll no0Sub = ((k * (k + 1)) % MOD) / 2;
            totSubArrays = (totSubArrays - no0Sub + MOD) % MOD;
        }

        reqSubArr = (reqSubArr + (totSubArrays * (1 << j)) % MOD) % MOD;
    }

    return reqSubArr % MOD;
}

int main() {
    return 0;
}
