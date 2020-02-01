/*
We are given a list schedule of employees, which represents the working time for each employee.
Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.
Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.
Example 1:
Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation:
There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.

Example 2:
Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined.)
Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.
Note:
schedule and schedule[i] are lists with lengths in range [1, 50].
0 <= schedule[i].start < schedule[i].end <= 10^8.
*/
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, pair<int, int>>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
// Time:  O(m * logn), m is the number of schedule, n is the number of employees, m >= n
// Space: O(n)

class Solution {
   public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        vector<Interval> res;
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        for (int i = 0; i < schedule.size(); i++)
            pq.push({schedule[i][0].start, {i, 0}});

        int last_end = -1;

        while (!pq.empty()) {
            auto [t, p] = pq.top();
            pq.pop();

            if (last_end >= 0 && last_end < t)
                res.emplace_back(last_end, t);
            last_end = max(last_end, schedule[p.first][p.second].end);
            if (p.second + 1 < schedule[p.first].size())
                pq.push({schedule[p.first][p.second + 1].start, {p.first, p.second + 1}});
        }

        return res;
    }
};

int main() {
    return 0;
}
