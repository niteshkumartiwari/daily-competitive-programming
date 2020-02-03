/*
Given an array w of positive integers, where w[i] describes the weight of index i, write a function pickIndex which randomly picks an index in proportion to its weight.

Note:

1 <= w.length <= 10000
1 <= w[i] <= 10^5
pickIndex will be called at most 10000 times.
Example 1:

Input: 
["Solution","pickIndex"]
[[[1]],[]]
Output: [null,0]
Example 2:

Input: 
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output: [null,0,1,1,1,0]
Explanation of Input Syntax:

The input is two lists: the subroutines called and their arguments. Solution's constructor has one argument, the array w. pickIndex has no arguments. Arguments are always wrapped with a list, even if there aren't any.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
    vector<int> sum;

   public:
    Solution(vector<int>& w) {
        srand(time(0));
        int n = w.size();
        sum.resize(n, 0);
        sum[0] = w[0];
        for (int i = 1; i < n; i++)
            sum[i] = sum[i - 1] + w[i];
    }

    int pickIndex() {
        int n = sum.size();
        int idx = rand() % (sum[n - 1]) + 1;
        int l = 0, r = n - 1;

        while (l < r) {
            int mid = l + (r - l) / 2;
            if (sum[mid] == idx)
                return mid;
            else if (sum[mid] < idx)
                l = mid + 1;
            else
                r = mid;
        }

        return l;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

int main() {
    return 0;
}
