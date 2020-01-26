/*
A sequence X_1, X_2, ..., X_n is fibonacci-like if:

n >= 3
X_i + X_{i+1} = X_{i+2} for all i + 2 <= n
Given a strictly increasing array A of positive integers forming a sequence, find the length of the longest fibonacci-like subsequence of A.  If one does not exist, return 0.

(Recall that a subsequence is derived from another sequence A by deleting any number of elements (including none) from A, without changing the order of the remaining elements.  For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].)

Example 1:

Input: [1,2,3,4,5,6,7,8]
Output: 5
Explanation:
The longest subsequence that is fibonacci-like: [1,2,3,5,8].
Example 2:

Input: [1,3,7,11,12,14,18]
Output: 3
Explanation:
The longest subsequence that is fibonacci-like:
[1,11,12], [3,11,14] or [7,11,18].
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int lenLongestFibSubseq(vector<int>& A) {
        int n = A.size();
        unordered_map<int, int> um;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        /*
            dp[i][j]:= # of fibo seq. ending with i,j
        */
        int res = 0;
        for (int i = 0; i < n; i++) {
            um[A[i]] = i;
            for (int j = 0; j < i; j++) {
                int k = um.count(A[i] - A[j]) ? um[A[i] - A[j]] : -1;
                dp[j][i] = (A[i] - A[j] < A[j] && k >= 0) ? dp[k][i] + 1 : 2;  //i bada h tu baad me aayega
                res = max(res, dp[j][i]);
            }
        }

        return res > 2 ? res : 0;
    }
};

int main() {
    return 0;
}
