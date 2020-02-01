/*
Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.
Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.
Example 1:
Input:
        1
       / \
      2   3
Output: 2
 Explanation: The longest consecutive path is [1, 2] or [2, 1].
Example 2:
Input:
        2
       / \
      1   3
Output: 3
 Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;

    TreeNode(int x) : data(x), left(NULL), right(NULL) {}
};

pair<int, int> longestPath(TreeNode *root) {
    if (!root) return {0, 0};

    int inc = 1, dec = 1;

    if (root->left) {
        auto left = longestPath(root->left);
        if (root->data == root->left->data + 1)
            dec = left.second + 1;
        if (root->data == root->left->data - 1)
            inc = left.first + 1;
    }

    if (root->right) {
        auto right = longestPath(root->right);
        if (root->data == root->right->data + 1)
            dec = max(dec, right.second + 1);
        if (root->data == root->right->data - 1)
            inc = max(inc, right.first + 1);
    }
    maxval = max(maxval, dec + inc - 1);
    return {inc, dec};
}

int maxval = 0;
int longestConsecutive(TreeNode *root) {
    longestPath(root);
    return maxval;
}

int main() {
    return 0;
}
