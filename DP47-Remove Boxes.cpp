/*
Given several boxes with different colors represented by different positive numbers.
You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
Find the maximum points you can get.

 

Example 1:

Input: boxes = [1,3,2,2,2,3,4,3,1]
Output: 23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1] 
----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
----> [1, 3, 3, 3, 1] (1*1=1 points) 
----> [1, 1] (3*3=9 points) 
----> [] (2*2=4 points)
 

Constraints:

1 <= boxes.length <= 100
1 <= boxes[i] <= 100
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();

        int dp[102][102][102];
        //max points we can get from i->j
        //such that k similar elements to i exists on its left.
        memset(dp, -1, sizeof dp);

        function<int(int, int, int)> go = [&](int i, int j, int k) {
            if (i > j) return 0;

            int& ans = dp[i][j][k];
            if (ans != -1) return ans;

            //for finding the similar contiguous values(sub-arrays)
            for (; i + 1 <= j && boxes[i] == boxes[i + 1]; i++, k++)
                ;

            int res = (k + 1) * (k + 1) + go(i + 1, j, 0);

            //considering subsequences
            for (int m = i + 1; m <= j; m++) {
                if (boxes[i] == boxes[m])
                    res = max(res, go(i + 1, m - 1, 0) + go(m, j, k + 1));
            }

            return ans = res;
        };

        return go(0, n - 1, 0);
        //from 0->n-1; 0 same letters on left
    }
};

int main() {
    return 0;
}
