/*
Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

 
Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
Pick out tallest group of people and sort them in a subarray (S). Since there's no other groups of people taller than them, therefore each guy's index will be just as same as his k value.
For 2nd tallest group (and the rest), insert each one of them into (S) by k value. So on and so forth.
E.g.
input: [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
subarray after step 1: [[7,0], [7,1]]
subarray after step 2: [[7,0], [6,1], [7,1]]
*/
//============== O(NlogN)==============
class SegmentTree {
   public:
    int N;
    vector<int> segmentTree;

    SegmentTree(int N) {
        this->N = N;
        this->segmentTree.resize(4 * N, 0);

        buildSegmentTree(1, 0, N - 1);
    }

    void buildSegmentTree(int idx, int l, int r) {
        if (l == r) {
            segmentTree[idx] = 1;
            return;
        }

        int mid = l + (r - l) / 2;

        buildSegmentTree(2 * idx, l, mid);

        buildSegmentTree(2 * idx + 1, mid + 1, r);

        //Core-logic for merge : TO-DO
        segmentTree[idx] = segmentTree[2 * idx] + segmentTree[2 * idx + 1];
    }

    int query(int idx, int l, int r, int val) {
        if (l == r)
            return l;

        int mid = l + (r - l) / 2;

        if (val <= segmentTree[2 * idx])
            return query(2 * idx, l, mid, val);
        else
            return query(2 * idx + 1, mid + 1, r, val - segmentTree[2 * idx]);
    }

    void update(int idx, int l, int r, int pos) {
        if (l == r) {
            segmentTree[idx] = 0;
            return;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid)
            update(2 * idx, l, mid, pos);
        else
            update(2 * idx + 1, mid + 1, r, pos);

        segmentTree[idx] = segmentTree[2 * idx] + segmentTree[2 * idx + 1];
    }
};

class Solution {
   public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int n = people.size();
        vector<vector<int>> ans(n);
        if (!n) return ans;

        sort(people.begin(), people.end(), [&](auto& a, auto& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });

        SegmentTree st = SegmentTree(n);

        for (auto person : people) {
            int pos = person[1] + 1;
            int idx = st.query(1, 0, n - 1, pos);
            ans[idx] = person;
            st.update(1, 0, n - 1, idx);
        }

        return ans;
    }
};

//============== O(N^2)==============
class Solution {  //O(n^2)
   public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](vector<int> a, vector<int> b) {
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
        });
        //dec order in height, if equal height then inc order in count

        vector<vector<int>> res;
        for (auto peep : people) {
            res.insert(res.begin() + peep[1], peep);
        }

        return res;
    }
};

int main() {
    return 0;
}
