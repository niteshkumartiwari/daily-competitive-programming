/*
Given an integer array arr, in one move you can select a palindromic subarray arr[i], arr[i+1], ..., arr[j] where i <= j, and remove that subarray from the given array. Note that after removing a subarray, the elements on the left and on the right of that subarray move to fill the gap left by the removal.
Return the minimum number of moves needed to remove all numbers from the array.

Example 1:
Input: arr = [1,2]
Output: 2
Example 2:
Input: arr = [1,3,4,1,5]
Output: 3
Explanation: Remove [4] then remove [1,3,1] then remove [5].

Constraints:
1 <= arr.length <= 100
1 <= arr[i] <= 20
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int minimumMoves(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = 1;
                continue;
            }
            dp[i][j] = 1 + dp[i + 1][j];  //can always remove the first
            //string
            if (arr[i] == arr[i + 1]) dp[i][j] = min(dp[i][j],
                                                     1 + dp[i + 2][j]);
            if (arr[i] == arr[j])
                dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);

            for (int k = i + 2; k < j; k++) {
                if (arr[i] == arr[k])
                    dp[i][j] = min(dp[i][j],
                                   dp[i + 1][k - 1] + dp[k + 1][j]);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    return 0;
}
/*
This question can be solved by dp. So the key is find the key logic, or state transfer equation.

Let use dp[i][j] represents the minimum number of moves needed to remove all the numbers from the array from i to j inclusive. Then,

(1) dp[i][j] = 1 + dp[i+1][j] //since it can ways be done by removing one by one;

(2) if(dp[i] == dp[i+1]), dp[i][j] = min(dp[i][j], 1 + dp[i+2][j]);

(3) if(dp[i] == dp[j]),  dp[i][j] = min(dp[i][j], dp[i+1][j-1])//both ends can be removed along with previous palindromes;

(4) if(dp[i] == dp[k]) dp[i][j] = min(dp[i][j], dp[i][k-1] + dp[k+1][j])  for k = i + 2, to j - 1;

Pay attention to the boundary conditions. The above (2) and (3) actually are the left and right boundaries of case (4).

Also pay attention to the for loops. The time complexity is O(N^3), and the dp is in a bottom-up building fashion. So we need to calculate each subarr with a smaller size or len. Then gradually build up the final dp[0][len-1]. 

*/