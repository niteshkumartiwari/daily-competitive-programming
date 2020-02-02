/*
On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

Examples:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]
Input: board = [[3,2,4],[1,5,0]]
Output: 14
Note:

board will be a 2 x 3 array as described above.
board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].
*/
#include <bits/stdc++.h>
#include <unordered_set>
#define ll long long
using namespace std;

class Solution {
   public:
    int slidingPuzzle(vector<vector<int>>& b) {
        string target = "123450";
        string begin = to_string(b[0][0]) + to_string(b[0][1]) + to_string(b[0][2]) + to_string(b[1][0]) + to_string(b[1][1]) + to_string(b[1][2]);

        vector<vector<int>> nextMoves{{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};

        unordered_set<string> visited{begin};
        queue<string> q;
        q.push(begin);

        for (int depth = 0; !q.empty(); ++depth) {
            int size = q.size();
            while (size--) {
                string u = q.front();
                q.pop();

                if (u == target) return depth;
                int zero = u.find("0");
                for (auto next : nextMoves[zero]) {
                    swap(u[zero], u[next]);
                    if (!visited.count(u)) {
                        visited.insert(u);
                        q.push(u);
                    }
                    swap(u[zero], u[next]);
                }
            }
        }

        return -1;
    }
};

int main() {
    return 0;
}

/*
Convert the board from vector<vector<int>> to a string representation of the board's first row values concatenated with the second row values. Consider this string the begin node which is pushed onto a queue q to perform BFS of a "graph" formed by pushing each non-visited next move onto the q ( pushing onto the q can be considered the equivalent of "connecting" the nodes in the "graph" where each candidate is connected one depth below the current depth. The depth corresponds to the amount of moves from begin to form a candidate. Please see example below for clarification ). Each next move is also stored as a string representation of the board with that next move performed by swap(). At each depth starting at 0, each candidate at that depth in q is checked to see if it is equal to target. When target is found, return depth, otherwise push all possible next moves onto the q in preparation for the next further depth to be checked during the next iteration of the outer-most for-loop. Keep track of previous candidates within visited to uniquely process candidates.

Example "graph":
The nodes are comprised of each candidate string, and nodes are "connected" to each other if they are not already visited and are one move away from each other...

board = {
{ 1,2,3 },
{ 4,0,5 },
};

begin = 123405

depth 0:           123405   <== 0 is at index 4, nextMoves[4]={1,3,5}, so swap 0 with the value
                 /   |    \       at each index 1,3,5 to form the next candidates to be pushed
                /    |     \      onto q in preparation for the next depth of processing
               /     |      \      
depth 1:    103425  123045  123450   <== next candidates pushed onto q
                           (target)
Since BFS is used, all candidates at each depth are checked before proceeding to the next depth. So for this example, depth=1 is returned, since the right-most candidate equals the target value 123450.
*/
