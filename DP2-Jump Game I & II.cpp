/*
JUMP I
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.
*/
#include <bits/stdc++.h>
using namespace std;

bool canJump(vector<int> jumps) {
    int dist = 0;
    int n = jumps.size();
    for (int i = 0; i <= dist; i++) {
        dist = max(dist, i + jumps[i]);
        if (dist >= n - 1) return true;
    }

    return false;
}

/*INCORRECT CODE
JUMP GAME II
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.
*/

bool canJump(vector<int> jump) {
    int jumps = 0, curEnd = 0, curFarthest = 0;

    for (int i = 0; i < jump.size(); i++) {
        curFarthest = max(curFarthest, jump[i] + i);

        if (curEnd == i) {
            jumps++;
            curEnd = curFarthest;
        }
    }

    return jumps;
}
/*
This is an implicit bfs solution. i == curEnd means you visited all the items on the current level. Incrementing jumps++ is like incrementing the level you are on. And curEnd = curFarthest is like getting the queue size (level size) for the next level you are traversing.
*/