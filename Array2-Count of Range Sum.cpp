/*
Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
    int mergeSort(vector<long>& prefix, int lower, int upper, int l, int r) {
        if (r - l <= 1) return 0;

        int mid = l + (r - l) / 2;
        int count = mergeSort(prefix, lower, upper, l, mid);
        count += mergeSort(prefix, lower, upper, mid, r);
        int j = mid, k = mid;
        for (int i = l; i < mid; i++) {
            while (j < r && prefix[j] - prefix[i] < lower) j++;
            while (k < r && prefix[k] - prefix[i] <= upper) k++;

            count += k - j;
        }

        inplace_merge(prefix.begin() + l, prefix.begin() + mid, prefix.begin() + r);
        return count;
    }

   public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long> prefixSum(n + 1, 0);

        for (int i = 0; i < n; i++)
            prefixSum[i + 1] = prefixSum[i] + nums[i];

        return mergeSort(prefixSum, lower, upper, 0, n + 1);
    }
};

int main() {
    return 0;
}
