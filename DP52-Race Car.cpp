/*
Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)

Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).

When you get an instruction "A", your car does the following: position += speed, speed *= 2.

When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)

For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.

Now for some target position, say the length of the shortest sequence of instructions to get there.

Example 1:
Input: 
target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0->1->3.
Example 2:
Input: 
target = 6
Output: 5
Explanation: 
The shortest instruction sequence is "AAARA".
Your position goes from 0->1->3->7->7->6.
 

Note:

1 <= target <= 10000.
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
    int dp[10005];
    int racecar(int target) {
        int n = floor(log2(target)) + 1;
        int &ans = dp[target];
        if (ans > 0) return ans;
        if (((1 << n) - 1) == target) return ans = n;

        int res = n + 1 + racecar((1 << n) - 1 - target);
        for (int m = 0; m < n - 1; m++) {
            res = min(res, racecar(target - ((1 << (n - 1)) - (1 << m))) + (n - 1) + 1 + m + 1);
        }

        return ans = res;
    }
};

int main() {
    Solution sol;
    cout << sol.racecar(6);

    return 0;
}