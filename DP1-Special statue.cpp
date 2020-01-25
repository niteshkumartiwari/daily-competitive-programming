/*
You are given N statues. The height of ith statue is given by Ai.
For the statues to be special, there should be no two consecutive statues of the same height.
If the given statues are not special, you can change the height of the statues. You can increase the height of the ith statue by 1 but have to pay Bi amount of money. Calculate the minimum amount of money you have to spend to make the statues special.

NOTE: The height of the statue can be increased any number of times(possibly 0).

Example Input
A = [2, 1, 1, 3, 4]
B = [3, 3, 5, 3, 10]


Example Output
5
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int solve(vector<int> &A, vector<int> &B) {
    int n = A.size();
    vector<vector<int>> dp(3, vector<int>(n, INT_MAX));
    /*
        claim: for min. amount spend we can only inc height by 0,1,2.

        dp[i][j]:= min amt of money you have to spend to make 
        jth element s.t. no two elements are together.
    */
    dp[0][0] = 0;
    dp[1][0] = B[0];
    dp[2][0] = 2 * B[0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= 2; j++) {      //add-height at curr index
            for (int k = 0; k <= 2; k++) {  //add-height at prev index
                if (A[i] + j != A[i - 1] + k)
                    dp[j][i] = min(dp[j][i], dp[k][i - 1] + B[i] * j);
            }
        }
    }

    return min({dp[0][n - 1], dp[1][n - 1], dp[2][n - 1]});
}

int main() {
    vector,
        return 0;
}
