/*
Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.

Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible..

Students must be placed in seats in good condition.

Example 1:


Input: seats = [["#",".","#","#",".","#"],
                [".","#","#","#","#","."],
                ["#",".","#","#",".","#"]]
Output: 4
Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam. 
Example 2:

Input: seats = [[".","#"],
                ["#","#"],
                ["#","."],
                ["#","#"],
                [".","#"]]
Output: 3
Explanation: Place all students in available seats. 

Example 3:

Input: seats = [["#",".",".",".","#"],
                [".","#",".","#","."],
                [".",".","#",".","."],
                [".","#",".","#","."],
                ["#",".",".",".","#"]]
Output: 10
Explanation: Place students in available seats in column 1, 3 and 5.
 

Constraints:

seats contains only characters '.' and'#'.
m == seats.length
n == seats[i].length
1 <= m <= 8
1 <= n <= 8
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
    int countSetBits(int n) {
        int count = 0;

        while (n) {
            n &= (n - 1);
            count++;
        }

        return count;
    }

   public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        vector<int> masks;
        for (int i = 0; i < m; ++i) {
            int cur = 0;
            for (int j = 0; j < n; ++j) {
                cur = cur * 2 + (seats[i][j] == '.');
            }
            masks.push_back(cur);
        }

        vector<vector<int>> dp(m + 1, vector<int>(1 << n, -1));
        dp[0][0] = 0;
        for (int i = 1; i <= m; ++i) {
            int valid = masks[i - 1];
            for (int j = 0; j < (1 << n); ++j) {
                if ((j & valid) == j && !(j & (j >> 1))) {
                    for (int k = 0; k < (1 << n); ++k) {
                        if (!(j & (k >> 1)) && !((j >> 1) & k) && dp[i - 1][k] != -1) {
                            dp[i][j] = max(dp[i][j], dp[i - 1][k] + countSetBits(j));
                        }
                    }
                }
            }
        }

        return *max_element(dp[m].begin(), dp[m].end());
    }
};

int main() {
    return 0;
}
/*
Bitmasking DP rarely appears in weekly contests. This tutorial will introduce my own perspective of bitmasking DP as well as several coding tricks when dealing with bitmasks. I will also give the solution to this problem at the end.

What is bitmasking? Bitmasking is something related to bit and mask. For the bit part, everything is encoded as a single bit, so the whole state can encoded as a group of bits, i.e. a binary number. For the mask part, we use 0/1 to represent the state of something. In most cases, 1 stands for the valid state while 0 stands for the invalid state.

Let us consider an example. There are 4 cards on the table and I am going to choose serveral of them. We can encode the 4 cards as 4 bits. Say, if we choose card 0, 1 and 3, we will use the binary number "1011" to represent the state. If we choose card 2, we will use binary number "0100" then. The bits on the right represent cards with smaller id.

As we all know, integers are store as binary numbers in the memory but appear as decimal numbers when we are coding. As a result, we tend to use a decimal number instead of a binary number to represent a state. In the previous example, we would use "11" and "4" instead of "1011" and "0100".

When doing Bitmasking DP, we must always handling problems like "what is the i-th bit in the state" or "what is the number of valid bits in a state". These problem can be very complicated if we do not handle them properly. I will show some coding tricks below which we can make use of and solve this problem.

We can use (x >> i) & 1 to get i-th bit in state x, where >> is the right shift operation. If we are doing this in a if statement (i.e. to check whether the i-th bit is 1), we can also use x & (1 << i), where the << is the left shift operation.

We can use (x & y) == x to check if x is a subset of y. The subset means every state in x could be 1 only if the corresponding state in y is 1.

We can use (x & (x >> 1)) == 0 to check if there are no adjancent valid states in x.

Now we can come to the problem. We can use a bitmask of n bits to represent the validity of each row in the classroom. The i-th bit is 1 if and only if the i-th seat is not broken. For the first example in this problem, the bitmasks will be "010010", "100001" and "010010". When we arrange the students to seat in this row, we can also use n bits to represent the students. The i-th bit is 1 if and only if the i-th seat is occupied by a student. We should notice that n bits representing students must be a subset of n bits representing seats.

We denote dp[i][mask] as the maximum number of students for the first i rows while the students in the i-th row follow the masking mask. There should be no adjancent valid states in mask. The transition function is:

dp[i][mask] = max(dp[i - 1][mask']) + number of valid bits(mask)
where mask' is the masking for the (i-1)-th row. In order to prevent students from cheating, the following equation must holds:

(mask & (mask' >> 1)) == 0, there should be no students in the upper left position for every student.

((mask >> 1) & mask') == 0, there should be no students in the upper right position for every student.

If these two equation holds and dp[i - 1][mask'] itself is valid, we could then transit from dp[i - 1][mask'] to dp[i][mask] according to the transition function.

And the last question is, how can we compute the number of valid bits in a masking efficiently? In C++, we can simply use the built-in function __builtin_popcount(mask). For other programming languages, we can pre-compute by using count[i] = count[i/2] + (i % 2 == 1) and store them in an array.
*/