/*
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Input: [5,2,6,1]
Output: [2,1,1,0] 

*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    void merge(vector<pair<int, int>> &items, int l, int mid, int h, vector<int> &res) {
        int m = h - l + 1;
        vector<pair<int, int>> sorted(m);
        int index = 0;
        int loPtr = l, hiPtr = mid + 1;
        int rightCounter = 0;

        while (loPtr <= mid && hiPtr <= h) {
            if (items[hiPtr].first < items[loPtr].first) {
                rightCounter++;
                sorted[index++] = items[hiPtr++];
            } else {  //  loPtr=5,6,7,10    hiPtr=1,2,3,20, rightCounter will start from 5
                res[items[loPtr].second] += rightCounter;
                sorted[index++] = items[loPtr++];
            }
        }

        while (loPtr <= mid) {
            res[items[loPtr].second] += rightCounter;
            sorted[index++] = items[loPtr++];
        }

        while (hiPtr <= h) {
            sorted[index++] = items[hiPtr++];
        }

        copy(sorted.begin(), sorted.begin() + m, items.begin() + l);
    }

    void mergeSort(vector<pair<int, int>> &items, int l, int h, vector<int> &res) {
        if (l >= h) return;
        int mid = l + (h - l) / 2;
        mergeSort(items, l, mid, res);
        mergeSort(items, mid + 1, h, res);
        merge(items, l, mid, h, res);
    }

    vector<int> countSmaller(vector<int> &nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        vector<pair<int, int>> items(n);

        for (int i = 0; i < n; i++)
            items[i] = {nums[i], i};

        mergeSort(items, 0, n - 1, res);
        return res;
    }
};  //O(nlogn)
/*
  5 2 6 1
5 2    6 1
5   2   6   1
2 5(1) 1 6(1)
1(0) 2(1) 5(2) 6(1)

*/

int main() {
    return 0;
}