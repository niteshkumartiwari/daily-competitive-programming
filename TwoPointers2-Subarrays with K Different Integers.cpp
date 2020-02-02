/*
Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.

(For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)

Return the number of good subarrays of A.

Example 1:

Input: A = [1,2,1,2,3], K = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
Example 2:

Input: A = [1,2,1,3,4], K = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 

Note:

1 <= A.length <= 20000
1 <= A[i] <= A.length
1 <= K <= A.length
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
Use a hashmap to store the frequency of each num, use a variable cnt to store the the number of different integers in the window.

Slide the right border j : If we meet a num with hash[j] == 0, cnt += 1. Find a sliding window with k different numbers .
Slide left border i if hash[A[i]] > 1, which means that there are more than one A[i] in the window. If we meet hash[A[i]] == 1 we cannot slide imore. Now we can build subarrays which start from the previous i(istart) to i and ends with j, and each of them has k different integers in it . That adds i - istart + 1 to our final answer.
Move on with the right border j, there are two situations:
If our cnt changes, we must move our left border i until cnt == k and reset istart.
If our cnt still equals to k(which means A[j] eauals to some existing value in the window), the subarrays which start from istart to i and ends with new j will still work(no more different number is added). We just need to move the left border i since the right border j may have same number with the left border and we only need one number to maintain the window. If we cannot slide more(hash[A[i]] == 1) , update our answer.
Since 1 <= A[i] <= A.length, we can use a vector instead of hashmap.
Complexity:

Time: O(N)
Space: O(N)
*/

class Solution {
   public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        int n = A.size();
        vector<int> hash(n + 1, 0);
        int res = 0;

        for (int i = 0, istart = 0, cnt = 0, j = 0; j < n; j++) {
            if (hash[A[j]]++ == 0) cnt++;
            if (cnt < K) continue;

            //got the window with >=K distinct elem

            //making sure its exactly K distinct elem
            while (cnt > K) {
                cnt -= (0 == --hash[A[i++]]);
                istart = i;
            }

            //get the more stricter window
            while (hash[A[i]] > 1) hash[A[i++]]--;
            res += i - istart + 1;
        }

        return res;
    }
};

int main() {
    return 0;
}
