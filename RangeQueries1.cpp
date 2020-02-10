/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:

The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
*/

class NumArray {
    vector<int> BIT;
    vector<int> num;

   public:
    NumArray(vector<int>& nums) {
        /*
            odd ones are only reponsible for themselfs,but
            even ones stores the # of elems equal to the the last set bits 
        */
        BIT.clear();
        num = nums;
        int n = nums.size();
        BIT.resize(n + 1, 0);

        for (int i = 0; i < n; i++)
            init(i, nums[i]);
    }

    void init(int i, int val) {  //go upstairs, which ever intervals are responsible add in them
        int n = num.size();

        i = i + 1;
        while (i <= n) {
            BIT[i] += val;
            i += i & -i;
        }
    }

    void update(int i, int val) {
        int diff = val - num[i];
        num[i] = val;
        init(i, diff);
    }

    int sumRange(int i) {  //go downstairs, get the sum from the intervals for whom this interval is responsible
        int sum = 0;
        i = i + 1;

        while (i > 0) {
            sum += BIT[i];
            i -= i & -i;
        }

        return sum;
    }

    int sumRange(int i, int j) {
        return sumRange(j) - sumRange(i - 1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    return 0;
}
