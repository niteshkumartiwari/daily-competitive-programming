/*
In an infinite binary tree where every node has two children, the nodes are labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.

Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.

Example 1:

Input: label = 14
Output: [1,3,4,14]
Example 2:

Input: label = 26
Output: [1,2,6,10,26]
 

Constraints:

1 <= label <= 10^6
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

//parent is always mirror-child/2
/*
Determine the tree level where our value is located. The maximum label in the level is 1 << level - 1, and minimum is 1 << (level - 1). We will use this fact to "invert" the parent label.
*/
class Solution {
   public:
    vector<int> pathInZigZagTree(int label) {
        int level = 0;
        while (1 << level <= label) level++;
        vector<int> res(level);
        for (; level >= 1; label /= 2, level--) {
            res[level - 1] = label;
            label = (1 << level) - 1 + (1 << (level - 1)) - label;
        }

        return res;
    }
};

int main() {
    return 0;
}
