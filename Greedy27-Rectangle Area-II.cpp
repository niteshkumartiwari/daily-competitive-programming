/*
We are given a list of (axis-aligned) rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] , where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner of the ith rectangle.

Find the total area covered by all rectangles in the plane. Since the answer may be too large, return it modulo 109 + 7.
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

/*----START CODING FROM HERE-------*/
class Solution {
   public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        vector<vector<int>> list;

        for (auto rect : rectangles) {
            list.push_back({rect[0], 0, rect[1], rect[3]});
            list.push_back({rect[2], 1, rect[1], rect[3]});
        }

        sort(list.begin(), list.end());

        multiset<pi> intervals;
        int area = 0, prevX = 0;

        auto getArea = [&](int width) {
            if (width == 0) return 0;
            int prev = 0, currArea = 0;

            for (auto interval : intervals) {
                interval.first = max(interval.first, prev);

                if (interval.second > interval.first) {
                    currArea += (interval.second - interval.first) * width;
                    prev = interval.second;
                }
            }

            return currArea;
        };

        for (int i = 0; i < list.size(); i++) {
            area = (area + getArea(list[i][0] - prevX)) % MOD;

            if (list[i][1] == 0)
                intervals.insert({list[i][2], list[i][3]});

            if (list[i][1] == 1) {
                auto itr = intervals.find({list[i][2], list[i][3]});
                if (itr != intervals.end()) {
                    intervals.erase(itr);
                }
            }

            prevX = list[i][0];
        }

        return area;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> num{
        {0, 0, 3, 3}, {2, 0, 5, 3}, {1, 1, 4, 4}};

    cout << sol.rectangleArea(num);

    return 0;
}