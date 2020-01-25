/*
Given an array of positive elements, you have to flip the sign of some of its elements such that the resultant sum of the elements of array should be minimum non-negative(as close to zero as possible). Return the minimum no. of elements whose sign needs to be flipped such that the resultant sum is minimum non-negative.

A = [14, 10, 4]
ans = 1 (Here, we will flip the sign of 14 and the resultant sum will be 0)
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int inf = 2e9;

int solve(vector<int> &A) {
    int n = A.size();
    int sum = 0;
    for (int val : A)
        sum += val;

    unordered_map<int, int> dp[2];
    /*
        min #of flip req. in first i elem
        to make the sum j.
	*/

    for (int i = -sum; i <= sum; i++)
        dp[0][i] = inf / 10;

    dp[0][0] = 0;
    int flag = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = -sum; j <= sum; j++) {
            dp[flag][j] = inf;

            if (j - A[i - 1] <= sum && j - A[i - 1] >= -sum)
                dp[flag][j] = dp[flag ^ 1][j - A[i - 1]];  //Don't flip

            if (j + A[i - 1] <= sum && j + A[i - 1] >= -sum)
                dp[flag][j] = min(dp[flag][j], dp[flag ^ 1][j + A[i - 1]] + 1);  //Flip it
        }

        flag ^= 1;
    }

    flag ^= 1;
    for (int i = 0; i <= sum; i++)
        if (dp[flag][i] != inf / 10)
            return dp[flag][i];

    return n - 1;
}

int main() {
    return 0;
}
/*
Naive approach: For each element A[i], 0 ≤ i < n of the array, we have 2 options.

1.Sign of A[i] is flipped(-ve).
2.Sign of A[i] is not flipped(+ve).
So we can have total 2n possible configurations of the array. We can maintain the sum of elements and number of flips in each configuration and keep a track of minimum sum (Ties are broken by the minimum number of flips).The number of flips in the minimum sum configuration will be the answer.
Time Complexity: O(2n) where n is number of elements in the array.

Efficient approach: This problem can be solved using dynamic programming and is a variation of standard 0/1 knapsack problem. The difference is that we have 2 options there i.e. either to include an item in the knapsack or exclude it and here it is like to flip the sign of element or not. Instead of bag weight in knapsack problem, here it is the sum of all elements of the array without flipping (which is maximum 104 given in problem statement).

Optimal Substructure: Let dp[i][j] be the minimum number of flips required in the first i elements of the array to make the sum equal to j.
1 ≤ i ≤ n and -sum ≤ j ≤ sum where sum is sum of all elements of array without flipping.

If sign of ar[i – 1] is not flipped to make sum = j
dp[i][j] = dp[i – 1][j – A[i – 1]]

If sign of ar[i – 1] is flipped to make sum = j
dp[i][j] = min(dp[i][j], dp[i – 1][j + A[i – 1]])

Note: Since the sum of elements of the array could be negative after flipping. So we can not use a 2D array for tabulation because in dp[i][j], j is the sum and indexes of the array cannot be negative. Thus, we are going to use an array of Hash maps. Size of the array will be n + 1.

Overlapping Subproblems: Just like 0/1 knapsack problem, there are overlapping subproblems here. We don’t need to evaluate results again and again but instead, we can store results of subproblems in a table.

Time complexity: O(n * sum)
Auxiliary Space: O(n * sum)
where n is number of elements and sum is sum of elements of the array without flipping.

Space optimization: If you take a closer look at the optimal substructure, dp[i][j] will depends only on dp[i – 1][j – A[i – 1]]/dp[i – 1][j + A[i – 1]]. So, there is involvement of only 2 rows i and i – 1. Thus, we need only 2 rows instead of n + 1.
Following are the changes that we need to optimize space.

Instead of taking array size=n+1 declare array of size=2.
Introduce a boolean variable (say flag) to toggle between maps.We can initialize dp[0] map and start filling dp[1].In the next iteration, dp[0] is the current map and dp[1] is previous.In this way, we can keep on toggling between the 2 maps.
*/
