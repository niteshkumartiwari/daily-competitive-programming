/*
We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group. What is the largest score we can achieve?

Note that our partition must use every number in A, and that scores are not necessarily integers.

Example:
Input: 
A = [9,1,2,3,9]
K = 3
Output: 20
Explanation: 
The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned A into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 

Note:

1 <= A.length <= 100.
1 <= A[i] <= 10000.
1 <= K <= A.length.
Answers within 10^-6 of the correct answer will be accepted as correct.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<vector<double>> dp;

class Solution {
    double go(vector<int> &sum, vector<int> &A, int K, int len, int s) {
        double &ans = dp[K][s];
        if (ans != 0) return ans;
        if (K == 1) return ans = (double)(sum[len - 1] - sum[s] + A[s]) / (len - s);
        double res = 0;
        for (int i = s; i + K <= len; i++) {
            res = max(res, (double)(sum[i] - sum[s] + A[s]) / (i - s + 1) +
                               go(sum, A, K - 1, len, i + 1));
        }

        return ans = res;
    }

   public:
    double largestSumOfAverages(vector<int> &A, int K) {
        int n = A.size();
        vector<int> sum(n, 0);
        dp.clear();
        dp.resize(105, vector<double>(105, 0));

        sum[0] = A[0];
        for (int i = 1; i < n; i++)
            sum[i] += sum[i - 1] + A[i];

        //return max. avg sum we can get after K partition

        return go(sum, A, K, n, 0);
    }
};

int main() {
    Solution sol = Solution();
    vector<int> A{9, 1, 2, 3, 9};
    int K = 3;
    cout << sol.largestSumOfAverages(A, K);
    return 0;
}
