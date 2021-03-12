/*
You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.

Return the minimum number of moves required so that nums has k consecutive 1's.

 

Example 1:

Input: nums = [1,0,0,1,0,1], k = 2
Output: 1
Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
Example 2:

Input: nums = [1,0,0,0,0,0,1,1], k = 3
Output: 5
Explanation: In 5 moves, the leftmost 1 can be shifted right until nums = [0,0,0,0,0,1,1,1].
Example 3:

Input: nums = [1,1,0,1], k = 2
Output: 0
Explanation: nums already has 2 consecutive 1's.
 

Constraints:

1 <= nums.length <= 105
nums[i] is 0 or 1.
1 <= k <= sum(nums)
*/

#include <bits/stdc++.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 100
#define ll long long
const int MOD = 1e9 + 7;
const int MAXBIT = 30;

void printArr(string str, vector<int> arr) {
    cout << str << endl;
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

/*----START CODING FROM HERE-------*/
class Solution {
   public:
    int minMoves(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ones;
        ones.push_back(0);
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) ones.push_back(i);
        }

        n = ones.size();
        vector<ll> prefix(n, 0);
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + ones[i];
        }

        printArr("ones", ones);
        printArr("prefix", prefix);

        int res = INT_MAX;

        int radius = (k - 1) / 2;
        for (int l = 1, r = k; r < n; l++, r++) {
            ll median = l + (k - 1) / 2;

            ll beforeMed = prefix[median - 1] - prefix[l - 1];
            ll afterMed = prefix[r] - prefix[median];
            ll distribute = (radius) * (radius + 1);

            ll ans = afterMed - beforeMed - distribute;
            if (k % 2 == 0) {
                ans -= ones[median];
                ans -= (radius + 1);
            }

            cout << ans << " " << afterMed << " " << beforeMed << " " << distribute << " " << (radius / 2 + 1) << endl;

            res = min(res, ans);
        }

        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums{1, 1, 0, 1};

    cout << sol.minMoves(nums, 2);

    // for(int val: res)
    //     cout<< val<<" ";

    return 0;
}