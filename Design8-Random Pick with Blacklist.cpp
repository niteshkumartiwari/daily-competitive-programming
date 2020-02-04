/*
Given a blacklist B containing unique integers from [0, N), write a function to return a uniform random integer from [0, N) which is NOT in B.

Optimize it such that it minimizes the call to system’s Math.random().

Note:

1 <= N <= 1000000000
0 <= B.length < min(100000, N)
[0, N) does NOT include N. See interval notation.
Example 1:

Input: 
["Solution","pick","pick","pick"]
[[1,[]],[],[],[]]
Output: [null,0,0,0]
Example 2:

Input: 
["Solution","pick","pick","pick"]
[[2,[]],[],[],[]]
Output: [null,1,1,1]
Example 3:

Input: 
["Solution","pick","pick","pick"]
[[3,[1]],[],[],[]]
Output: [null,0,0,2]
Example 4:

Input: 
["Solution","pick","pick","pick"]
[[4,[2]],[],[],[]]
Output: [null,1,3,1]
Explanation of Input Syntax:

The input is two lists: the subroutines called and their arguments. Solution's constructor has two arguments, N and the blacklist B. pick has no arguments. Arguments are always wrapped with a list, even if there aren't any.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

//Suppose N=10, blacklist=[3, 5, 8, 9], re-map 3 and 5 to 7 and 6.
class Solution {
    int M;
    unordered_map<int, int> map;

   public:
    Solution(int N, vector<int>& blacklist) {
        for (int b : blacklist) {
            if (b < N) map[b] = -1;
        }

        M = N - map.size();
        for (int b : blacklist) {
            if (b < M) {
                while (map.count(--N)) {
                };
                map[b] = N;
            }
        }
    }

    int pick() {
        int idx = rand() % M;
        if (map.count(idx))
            return map[idx];
        return idx;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
 */

int main() {
    return 0;
}
