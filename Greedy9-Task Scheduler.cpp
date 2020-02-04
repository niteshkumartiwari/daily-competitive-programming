/*
Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks. Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

 

Example:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
 

Note:

The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Solution {
   public:
    int leastInterval(vector<char>& tasks, int k) {
        int n = tasks.size();
        vector<int> count(26, 0);
        int maxCount = 0;
        for (auto task : tasks) {
            count[task - 'A']++;
            maxCount = max(maxCount, count[task - 'A']);
        }

        int ans = (maxCount - 1) * (k + 1);
        for (auto val : count)
            if (val == maxCount) ans++;

        return max(ans, n);
    }
};

int main() {
    return 0;
}

/*
First count the number of occurrences of each element.
Let the max frequency seen be M for element E
We can schedule the first M-1 occurrences of E, each E will be followed by at least N CPU cycles in between successive schedules of E
Total CPU cycles after scheduling M-1 occurrences of E = (M-1) * (N + 1) // 1 comes for the CPU cycle for E itself
Now schedule the final round of tasks. We will need at least 1 CPU cycle of the last occurrence of E. If there are multiple tasks with frequency M, they will all need 1 more cycle.
Run through the frequency dictionary and for every element which has frequency == M, add 1 cycle to result.
If we have more number of tasks than the max slots we need as computed above we will return the length of the tasks array as we need at least those many CPU cycles.
*/
