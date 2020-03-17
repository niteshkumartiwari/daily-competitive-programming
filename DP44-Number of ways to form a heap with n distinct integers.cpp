/*
Since there is only one element as the root, it must be the largest number. Now we have n-1 remaining elements. The main observation here is that because of the max heap properties, the structure of the heap nodes will remain the same in all instances, but only the values in the nodes will change.

Assume there are l elements in the left sub-tree and r elements in the right sub-tree. Now for the root, l + r = n-1. From this we can see that we can choose any l of the remaining n-1 elements for the left sub-tree as they are all smaller than the root.
We know the there are  \binom{n-1}{l}  ways to do this. Next for each instance of these, we can have many heaps with l elements and for each of those we can have many heaps with r elements. Thus we can consider them as subproblems and recur for the final answer as:
T(n) = \binom{n-1}{l}  * T(L) * T(R).

Now we have to find the values for l and r for a given n. We know that the height of the heap h = \log_2 n. Also the maximum number of elements that can be present in the h th level of any heap, m = 2^h, where the root is at the 0th level. Moreover the number of elements actually present in the last level of the heap p = n – (2^h – 1). (since 2^h - 1 number of nodes present till the penultimate level). Thus, there can be two cases: when the last level is more than or equal to half-filled:
l = 2^h – 1, if p >= m / 2
(or) the last level is less than half-filled:
l = 2^h – 1 – ((m / 2) – p), if p < m / 2
(we get 2^h– 1 here because left subtree has 2^0 + 2^1 +..+2^{h-1} nodes.
From this we can also say that r = n – l – 1.

We can use the dynamic programming approach discussed in this post here to find the values of \binom{n}{k}. Similarly if we look at the recursion tree for the optimal substructure recurrence formed above, we can see that it also has overlapping subproblems property, hence can be solved using dynamic programming:

             T(7)
            /    \
          T(3)   T(3)
         /  \     /  \    
     T(1)  T(1) T(1) T(1) 
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll MOD = 1e9 + 7;

int comb[109][109];
int nCr(int n, int r) {
    int &res = comb[n][r];
    if (res != -1) return res;

    if (r > n)
        return res = 0;
    if (n <= 1)
        return res = 1;

    res = nCr(n - 1, r - 1) + nCr(n - 1, r);

    return res;
}

int getLeft(int n) {
    int h = log2(n);
    int maxNodesAtH = (1 << h);
    int lastLevel = n - (maxNodesAtH - 1);

    if (lastLevel >= maxNodesAtH / 2)
        return maxNodesAtH - 1;
    else
        return (maxNodesAtH - 1 - (maxNodesAtH / 2 - lastLevel));
}

int solve(int n) {
    if (n <= 1) return 1;
    vector<int> dp(n + 1, -1);
    memset(comb, -1, sizeof comb);
    function<int(int)> numberOfHeaps = [&](int n) {
        int &ans = dp[n];
        if (ans != -1) return dp[n];

        if (n <= 1) return 1;

        int left = getLeft(n);
        ans = nCr(n - 1, left) * numberOfHeaps(left) * numberOfHeaps(n - left);

        return ans;
    };

    return numberOfHeaps(n);
}

int main() {
    cout << solve(4);
    return 0;
}
