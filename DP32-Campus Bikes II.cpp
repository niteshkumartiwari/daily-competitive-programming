/*
On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.
We assign one unique bike to each worker so that the sum of the Manhattan distances between each worker and their assigned bike is minimized.
The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.
Return the minimum possible sum of Manhattan distances between each worker and their assigned bike.

Example 1:

Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: 6
Explanation: 
We assign bike 0 to worker 0, bike 1 to worker 1. The Manhattan distance of both assignments is 3, so the output is 6.
Example 2:

Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: 4
Explanation: 
We first assign bike 0 to worker 0, then assign bike 1 to worker 1 or worker 2, bike 2 to worker 2 or worker 1. Both assignments lead to sum of the Manhattan distances as 4.

Note:
0 <= workers[i][0], workers[i][1], bikes[i][0], bikes[i][1] < 1000
All worker and bike locations are distinct.
1 <= workers.length <= bikes.length <= 10

*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int minManhattDist(vector<vector<int>> &ws, vector<vector<int>> &bs) {
    int m = ws.size(), n = bs.size();
    vector<vector<int>> dp(1 << m, vector<int>(1 << n, -1));

    function<int(int, int, int)> dfs = [&](int i, int st1, int st2) {
        if (i == m) return 0;  //all the workers are assigned;
        int &ans = dp[st1][st2];
        if (ans != -1) return ans;
        int minDist = INT_MAX;

        for (int j = 0; j < n; j++) {      //try all the bikes;
            if ((st2 >> j) & 1) continue;  //if the bike is used;
            int dist = abs(ws[i][0] - bs[j][0]) + abs(ws[i][1] - bs[j][1]);
            dist += dfs(i + 1, st1 | (1 << i), st2 | (1 << j));  //total dis in this case;
            minDist = min(minDist, dist);                        //min distance;
        }

        return ans = minDist;
    };

    return dfs(0, 0, 0);
}

int main() {
    return 0;
}

/*
Notes:

It is said that this question is from one of the onsite interviews of Google company.

The naive method is that we try all the possible combinations using backtracking, but apparently we re-calculate a lot of sub-states.

In order to better see this, let us consider two cases. One is that we let worker 1 choose bike 1, and worker 2 pick bike 2, then the rest workers choose the rest bikes (sub-state 1). The other case is that, worker 1 chooses bike 2, and worker 2 chooses bike 1, then the rest workers choose the rest bikes (sub-state 2). Apparently, sub-state 1 is the same as sub-state 2, so we just need to calculate it once, and then re-use the result directly if need it again.

To this question, bit mapping is a naturally choice to label the state. 0 represents un-used and 1 represents used. (The very small values of the number of both workers and bikes are good indicators to this.)

Since both the number of the workers and bikes are no larger than 10, an integer (32 bits) should be enough to record it. Thus, we can use two integers to memorize the combination conditions between workers and bikes. In the following code, integer state1 is for workers, and integer state2 for bikes.

Suppose there are N workers and M bikes, the total possible states is (2^N)*(2^M). So the space  complexity is O((2^N)*(2^M)). Since we only calculate once for each state, the time complexity is the same as the space complexity.

[update on 10/07/2019]: The time complexity is O(N*M*2^N*2^M), since for each substate calculation, or local minimum, we have run all the possible matches between workers and bikes.]  
*/