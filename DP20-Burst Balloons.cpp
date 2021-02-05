/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a
 number on it represented by array nums. You are asked to burst all the
balloons. If the you burst balloon i you will get nums[left] * nums[i] *
nums[right] coins. Here left and right are adjacent indices of i. After
the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Input: [3,1,5,8]
Output: 167 
Explanation: nums = [3,1,5,8]-->[3,5,8]-->[3,8]-->[8]--> []
             coins =  3*1*5   +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int solve(vector<int> &A) {
    A.push_back(1);
    A.insert(A.begin(), 1);
    int n = A.size();

    vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
    /*
		dp[i][j]:= max coins we can collect by bursting baloons in [i,j]
		i-1,i,i+1.........k......j-1,j,j+1
	*/
    n -= 2;

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i < n; i++) {
            int j = i + len - 1;

            for (int k = i; k <= j; k++) {
                int val = 0;
                val += (dp[i][k - 1] != INT_MIN) ? dp[i][k - 1] : 0;
                val += (dp[k + 1][j] != INT_MIN) ? dp[k + 1][j] : 0;
                dp[i][j] = max(dp[i][j], val + A[i - 1] * A[k] * A[j + 1]);
            }
        }
    }

    return dp[1][n];
}

int main() {
    vector<int> A{4, 2, 6, 7};
    cout << "ans is" << endl;
    cout << solve(A);
    return 0;
}

/*
dp[i][j]: coins obtained from bursting all the balloons between index i and j (not including i or j)
dp[i][j] = max(nums[i] * nums[k] * nums[j] + dp[i][k] + dp[k][j]) (k in (i+1,j))
If k is the index of the last balloon burst in (i, j), the coins that burst will get are nums[i] * nums[k] * nums[j], and to calculate dp[i][j], we also need to add the coins obtained from bursting balloons between i and k, and between k and j, i.e., dp[i][k] and dp[k][j]
*/

//Extended Approach

/*
Be Naive First

When I first get this problem, it is far from dynamic programming to me. I started with the most naive idea the backtracking.

We have n balloons to burst, which mean we have n steps in the game. In the i th step we have n-i balloons to burst, i = 0~n-1. Therefore we are looking at an algorithm of O(n!). Well, it is slow, probably works for n < 12 only.

Of course this is not the point to implement it. We need to identify the redundant works we did in it and try to optimize.

Well, we can find that for any balloons left the maxCoins does not depends on the balloons already bursted. This indicate that we can use memorization (top down) or dynamic programming (bottom up) for all the cases from small numbers of balloon until n balloons. How many cases are there? For k balloons there are C(n, k) cases and for each case it need to scan the k balloons to compare. The sum is quite big still. It is better than O(n!) but worse than O(2^n).

Better idea

We then think can we apply the divide and conquer technique? After all there seems to be many self similar sub problems from the previous analysis.

Well, the nature way to divide the problem is burst one balloon and separate the balloons into 2 sub sections one on the left and one one the right. However, in this problem the left and right become adjacent and have effects on the maxCoins in the future.

Then another interesting idea come up. Which is quite often seen in dp problem analysis. That is reverse thinking. Like I said the coins you get for a balloon does not depend on the balloons already burst. Therefore
instead of divide the problem by the first balloon to burst, we divide the problem by the last balloon to burst.

Why is that? Because only the first and last balloons we are sure of their adjacent balloons before hand!

For the first we have nums[i-1]*nums[i]*nums[i+1] for the last we have nums[-1]*nums[i]*nums[n].

OK. Think about n balloons if i is the last one to burst, what now?

We can see that the balloons is again separated into 2 sections. But this time since the balloon i is the last balloon of all to burst, the left and right section now has well defined boundary and do not affect each other! Therefore we can do either recursive method with memoization or dp.
*/
