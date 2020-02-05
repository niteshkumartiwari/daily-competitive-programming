/*
In combinatorial mathematics, a derangement is a permutation of the elements of a set, such that no element appears in its original position.
There's originally an array consisting of  n integers from 1 to  n in ascending order, you need to find the number of derangement it can generate.
Also, since the answer may be very large, you should return the output mod 10 9  + 7.
Example 1:
Input: 3
 Output: 2
 Explanation: The original array is [1,2,3]. The two derangements are [2,3,1] and [3,1,2].
Note:
n  is in the range of [1, 10 6 ].
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int cntDerangements(int n) {
    vector<int> dp(n + 1, 0);

    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 1;

    for (int i = 3; i <= n; i++)
        dp[i] = (dp[i - 2] + dp[i - 1]) * (i - 1);

    return dp[n];
}

int main() {
    cout << cntDerangements(4);
    return 0;
}

/*
Let countDer(n) be count of derangements for n elements. Below is recursive relation for it.

countDer(n) = (n - 1) * [countDer(n - 1) + countDer(n - 2)]
How does above recursive relation work?
There are n – 1 ways for element 0 (this explains multiplication with n – 1).

Let 0 be placed at index i. There are now two possibilities, depending on whether or not element i is placed at 0 in return.

i is placed at 0: This case is equivalent to solving the problem for n-2 elements as two elements have just swapped their positions.
i is not placed at 0: This case is equivalent to solving the problem for n-1 elements as now there are n-1 elements, n-1 positions and every element has n-2 choices
*/