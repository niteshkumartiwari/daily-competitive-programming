/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Your job is to output the median array for each window in the original array.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Median
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
Therefore, return the median sliding window as [1,-1,-1,3,5,6].

Note:
You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
Answers within 10^-5 of the actual value will be accepted as correct.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {  //nlogk
        multiset<int> window(nums.begin(), nums.begin() + k);
        auto mid = next(window.begin(), k / 2);
        vector<double> medians;

        for (int i = k;; i++) {
            //push the current median
            medians.push_back((double(*mid) + *prev(mid, 1 - k % 2)) / 2);

            //If all done
            if (i == nums.size()) return medians;

            //Insert nums[i]
            window.insert(nums[i]);
            if (nums[i] < *mid)
                mid--;

            /*
            Just a simple note: "in C++11, newly inserted elements 
            follow their equivalents already in the container."
            Thus, when nums[i] == *mid, we do not need to decrease mid, 
            since nums[i] will inserted after mid.
            */

            if (nums[i - k] <= *mid)
                mid++;

            window.erase(window.lower_bound(nums[i - k]));
        }
    }
};

/*
Insertion
        m
    1 2 3 4 5
                     m<- m(change median)
1. num[i]=2.5 => 1 2 2.5 3 4 5
                     m->m(automatically incr m)
2. num[i]=3.5 => 1 2 3 3.5 4 5

Deletion
1. num[i-k]=2
          m->m(median-change)
        1 3  4  5
2. num[i-k]=5
          m<-m(automatically decrease m)
        1 2 3 4

*/

int main() {
    return 0;
}
