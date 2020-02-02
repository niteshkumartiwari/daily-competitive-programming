/*
Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals.

For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
 

Follow up:

What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Interval {
    int start, end;

    Interval(int s, int e) : start(s), end(e) {}
    bool operator<(const Interval& t) const {
        return (this->start < t.start);
    }
};

class SummaryRanges {
    set<Interval> s;

   public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        s.clear();
    }

    void addNum(int val) {
        auto it = s.lower_bound(Interval(val, val));  //BS on interval
        int start = val, end = val;

        if (it != s.begin() && (--it)->end + 1 < val) it++;

        while (it != s.end() && val + 1 >= it->start && val - 1 <= it->end) {
            start = min(it->start, start);
            end = max(end, it->end);
            it = s.erase(it);
        }

        s.insert(it, Interval(start, end));
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> res;
        for (auto inte : s)
            res.push_back({inte.start, inte.end});

        return res;
    }
};
/*
First, run lower_bound let it point to interval (8,9) because 8 is the first element that is >= 7

(0,2) (4,6) (8,9) (12,15)    temp = (7, 7)
             ^
We decrement it because the previous interval can merge 7

(0,2) (4,6) (8,9) (12,15)    temp = (7, 7)
       ^
Now, it points to the first mergeable interval (if there is one). In this case, (4,6).
While this interval is mergeable, merge (4,6) with temp to get

(0,2) (8,9) (12,15)          temp = (4, 7)
       ^
Merge (8,9) with temp to get

(0,2) (12,15)                temp = (4, 9)
       ^
Can't merge anymore, insert temp

(0,2) (4,9) (12,15)          temp = (4, 9)
*/

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */

int main() {
    return 0;
}
