/*
In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

Example:

Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
 

Note:

nums.length will be between 1 and 20000.
nums[i] will be between 1 and 65535.
k will be between 1 and floor(nums.length / 3).
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n, 0);  //subarray sum of size k starting at i
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += nums[i];

            if (i >= k)  // to maintain a window of size k
                sum -= nums[i - k];

            if (i >= k - 1)
                dp[i - k + 1] = sum;
        }

        vector<int> left(n, 0);
        int maxIndex = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] > dp[maxIndex])
                maxIndex = i;
            left[i] = maxIndex;
        }

        vector<int> right(n, 0);
        maxIndex = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (dp[i] >= dp[maxIndex])
                maxIndex = i;
            right[i] = maxIndex;
        }

        vector<int> res(3, -1);
        for (int i = k; i < n - k; i++) {
            if (res[0] == -1 ||
                dp[res[0]] + dp[res[1]] + dp[res[2]] < dp[left[i - k]] + dp[i] + dp[right[i + k]]) {
                res[0] = left[i - k];
                res[1] = i;
                res[2] = right[i + k];
            }
        }

        return res;
    }
};

int main() {
    return 0;
}
