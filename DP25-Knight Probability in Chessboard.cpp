/*
On an NxN chessboard, a knight starts at the r-th row and c-th column and attempts to make exactly K moves. The rows and columns are 0 indexed, so the top-left square is (0, 0), and the bottom-right square is (N-1, N-1).

A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly K moves or has moved off the chessboard. Return the probability that the knight remains on the board after it has stopped moving.

Example:

Input: 3, 2, 0, 0
Output: 0.0625
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.
 

Note:

N will be between 1 and 25.
K will be between 0 and 100.
The knight always initially starts on the board.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    double knightProbability(int N, int K, int r, int c) {
        double dp[30][30][105] = {0};
        // direction vector for the Knight
        int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                dp[i][j][0] = 1;

        //for every #of steps
        for (int s = 1; s <= K; s++) {
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    double prob = 0.0;

                    for (int k = 0; k < 8; k++) {
                        int vx = x + dx[k], vy = y + dy[k];
                        if (vx < 0 || vx >= N || vy < 0 || vy >= N) continue;

                        prob += dp[vx][vy][s - 1] / 8.0;
                    }

                    dp[x][y][s] = prob;
                }
            }
        }

        return dp[r][c][K];
    }
};

int main() {
    return 0;
}

/*
One thing that we can observe is that at every step the Knight has 8 choices to choose from. Suppose, the Knight has to take k steps and after taking the Kth step the knight reaches (x,y). There are 8 different positions from where the Knight can reach to (x,y) in one step, and they are: (x+1,y+2), (x+2,y+1), (x+2,y-1), (x+1,y-2), (x-1,y-2), (x-2,y-1), (x-2,y+1), (x-1,y+2).
What if we already knew the probabilities of reaching these 8 positions after K-1 steps? Then, the final probability after K steps will simply be equal to the (Σ probability of reaching each of these 8 positions after K-1 steps)/8;
Here we are dividing by 8 because each of these 8 positions have 8 choices and position (x,y) is one of the choice.
For the positions that lie outside the board, we will either take their probabilities as 0 or simply neglect it.

Since, we need to keep track of the probabilities at each position for every number of steps, we need Dynamic Programming to solve this problem.
We are going to take an array dp[x][y][steps] which will store the probability of reaching (x,y) after (steps) number of moves.
Base case : if number of steps is 0, then the probability that the Knight will remain inside the board is 1.

*/
