/*
Given a sorted array, two integers k and x, find the k closest elements to x in the array. The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

Example 1:
Input: [1,2,3,4,5], k=4, x=3
Output: [1,2,3,4]
Example 2:
Input: [1,2,3,4,5], k=4, x=-1
Output: [1,2,3,4]
Note:
The value k is positive and will always be smaller than the length of the sorted array.
Length of the given array is positive and will not exceed 104
Absolute value of elements in the array and x will not exceed 104
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
/*
Assume we are taking A[i] ~ A[i + k -1].
We can binary research i
We compare the distance between x - A[mid] and A[mid + k] - x

If x - A[mid] > A[mid + k] - x,
it means A[mid + 1] ~ A[mid + k] is better than A[mid] ~ A[mid + k - 1],
and we have mid smaller than the right i.
So assign left = mid + 1.

Note that, you SHOULD NOT compare the absolute value of abs(x - A[mid]) and abs(A[mid + k] - x).
It fails at cases like A = [1,1,2,2,2,2,2,3,3], x = 3, k = 3
*/

class Solution {  //log(N-K)+K
   public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int l = 0, r = n - k;

        while (l < r) {
            int mid = l + (r - l) / 2;
            if (x - arr[mid] > arr[mid + k] - x)
                l = mid + 1;
            else
                r = mid;
        }

        return vector<int>(arr.begin() + l, arr.begin() + l + k);
    }
};

int main() {
    return 0;
}
