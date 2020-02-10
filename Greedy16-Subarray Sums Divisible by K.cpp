/*
Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.

 

Example 1:

Input: A = [4,5,0,-2,-3,1], K = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by K = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 

Note:

1 <= A.length <= 30000
-10000 <= A[i] <= 10000
2 <= K <= 10000
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
About the problems - sum of contiguous subarray , prefix sum is a common technique.
Another thing is if sum[0, i] % K == sum[0, j] % K, sum[i + 1, j] is divisible by by K.
So for current index j, we need to find out how many index i (i < j) exit that has the same mod of K.
Now it easy to come up with HashMap <mod, frequency>

Time Complexity: O(N)
Space Complexity: O(K)

*/

class Solution {
   public:
    int subarraysDivByK(vector<int>& A, int K) {
        int n = A.size();
        int sum = 0, count = 0;
        vector<int> map(K, 0);
        map[0] = 1;  // for sum=0;
        for (int i = 0; i < n; i++) {
            sum = (sum + A[i]) % K;
            if (sum < 0) sum += K;  //we want +ve MOD
            count += map[sum];
            map[sum]++;
        }

        return count;
    }
};

int main() {
    return 0;
}
