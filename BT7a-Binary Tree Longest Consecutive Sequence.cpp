/*
Given a binary tree, find the length of the longest consecutive sequence path.
The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path needs to be from parent to child (cannot be the reverse).
For example,
   1
    \
     3
    / \
   twenty four
        \
         5
Longest consecutive sequence path is  3-4-5, so return  3.
   2
    \
     3
    / 
   2    
  / 
 1
Longest consecutive sequence path is  2-3, not 3-2-1, so return  2.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

// Time complexity:  O(n) given there are  n nodes in the tree.
// Space complexity:  O(n) for the recursion stack.

struct TreeNode {
    int data;
    TreeNode *left, *right;

    TreeNode(int x) : data(x), left(NULL), right(NULL) {}
};

int res = 0;

int getLongestConsecutive(TreeNode *root) {
    int ret = 1;
    if (root->left) {
        int left = getLongestConsecutive(root->left);
        if (root->data == root->left->data - 1)
            ret = max(ret, 1 + left);
    }

    if (root->right) {
        int right = getLongestConsecutive(root->right);
        if (root->data == root->right->data - 1)
            ret = max(ret, 1 + right);
    }

    res = max(res, ret);

    return ret;
}

int longestConsecutive(TreeNode *root) {
    if (root == NULL) return 0;

    getLongestConsecutive(root);

    return res;
}

int main() {
    return 0;
}
