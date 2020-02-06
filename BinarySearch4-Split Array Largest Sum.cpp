/*
Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

Note:
If n is the length of array, assume the following constraints are satisfied:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
    bool isValid(ll target, vector<int>& nums, int m) {
        int count = 1;
        ll tot = 0;
        for (int num : nums) {
            tot += num;

            if (tot > target) {
                count++;
                tot = num;

                if (count > m) return false;
            }
        }

        return true;
    }

   public:
    int splitArray(vector<int>& nums, int m) {
        int maxVal = 0;
        ll sum = 0;
        for (int num : nums) {
            maxVal = max(maxVal, num);
            sum += num;
        }
        if (m == 1) return sum;
        ll l = maxVal, r = sum;

        while (l <= r) {
            ll mid = l + (r - l) / 2;

            if (isValid(mid, nums, m))
                r = mid - 1;
            else
                l = mid + 1;
        }

        return l;
    }
};

int main() {
    return 0;
}
