/*
You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Note:
Rotation is not allowed.

Example:

Input: [[5,4],[6,4],[6,7],[2,3]]
Output: 3 
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

//Approach 1: O(N^2)
/*Vanilla LIS approach*/
bool custom(vector<int> a, vector<int> b) {
    if (a[0] != b[0])
        return a[0] < b[0];
    return a[1] < b[1];
}

int solve(vector<vector<int>>& A) {
    int n = A.size();

    vector<int> dp(n, 1);
    sort(A.begin(), A.end(), custom);
    int ans = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j][0] < A[i][0] && A[j][1] < A[i][1] && dp[j] + 1 > dp[i])
                dp[i] = dp[j] + 1;
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}

//Approach 2: O(nlogn)

/*
Sort the array. Ascend on width and descend on height if width are same.
Find the longest increasing subsequence based on height.
*/

class Solution {
   public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), [](vector<int> a, vector<int> b) {
            if (a[0] == b[0])
                return a[1] > b[1];  //hight descending order
            return a[0] < b[0];      //width ascending order
        });

        vector<int> dp;
        for (auto& env : envelopes) {  //only storing LIS in the array
            auto itr = lower_bound(dp.begin(), dp.end(),
                                   env[1]);
            if (itr == dp.end())
                dp.push_back(env[1]);
            else if (*itr > env[1])
                *itr = env[1];
        }

        return dp.size();
    }
};

int main() {
    return 0;
}

/*
This problem is asking for LIS in two dimensions, width and height. Sorting the width reduces the problem by one dimension. If width is strictly increasing, the problem is equivalent to finding LIS in only the height dimension. However, when there is a tie in width, a strictly increasing sequence in height may not be a correct solution. For example, [[3,3] cannot fit in [3,4]]. Sorting height in descending order when there is a tie prevents such a sequence to be included in the solution.

The same idea can be applied to problems of higher dimensions. For example, box fitting is three dimensions, width, height, and length. Sorting width ascending and height descending reduces the problem by one dimension. Finding the LIS by height further reduces the problem by another dimension. When find LIS based on only length, it becomes a standard LIS problem.

*/
