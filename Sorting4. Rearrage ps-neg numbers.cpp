/*
Given an array of positive and negative numbers, arrange them such that all negative integers appear before all the positive integers in the array without using any additional data structure like hash table, arrays, etc. The order of appearance should be maintained.
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
   private:
    void reverse(vector<int> &A, int l, int r) {
        while (l < r) {
            swap(A[l], A[r]);
            l++;
            r--;
        }
    }
    void merge(vector<int> &A, int l, int mid, int r) {
        int i = l, j = mid + 1;

        while (i <= mid && A[i] < 0) i++;
        while (j <= r && A[j] < 0) j++;

        reverse(A, i, mid);
        reverse(A, mid + 1, j - 1);
        reverse(A, i, j - 1);
    }

    void mergeSort(vector<int> &A, int l, int r) {
        if (l >= r) return;
        int mid = l + (r - l) / 2;

        mergeSort(A, l, mid);
        mergeSort(A, mid + 1, r);

        merge(A, l, mid, r);
    }

   public:
    void solve(vector<int> &A) {
        int n = A.size();
        mergeSort(A, 0, n - 1);
    }
};

int main() {
    Solution sol;
    vector<int> nums{12, 11, -13, -5, 6, -7, 5, -3, -6};

    sol.solve(nums);

    for (int val : nums)
        cout << val << " ";
    return 0;
}