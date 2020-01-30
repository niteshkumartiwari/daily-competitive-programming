/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        vector<vector<int>> res;
        int index = 0;

        while (index < n && intervals[index][1] < newInterval[0])
            res.push_back(intervals[index++]);

        while (index < n && intervals[index][0] <= newInterval[1]) {  //start1<=endNew
            newInterval[0] = min(newInterval[0], intervals[index][0]);
            newInterval[1] = max(newInterval[1], intervals[index][1]);
            index++;
        }

        res.push_back(newInterval);
        while (index < n)
            res.push_back(intervals[index++]);

        return res;
    }
};

int main() {
    return 0;
}
