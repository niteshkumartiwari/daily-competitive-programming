/*
Given a Binary Search Tree (BST) with root node root, and a target value V, split the tree into two subtrees where one subtree has nodes that are all smaller or equal to the target value, while the other subtree has all nodes that are greater than the target value.  It's not necessarily the case that the tree contains a node with value V.
Additionally, most of the structure of the original tree should remain.  Formally, for any child C with parent P in the original tree, if they are both in the same subtree after the split, then node C should still have the parent P.
You should output the root TreeNode of both subtrees after splitting, in any order.
Example 1:
Input: root = [4,2,6,1,3,5,7], V = 2
Output: [[2,1],[4,3,6,null,null,5,7]]
Explanation:
Note that root, output[0], and output[1] are TreeNode objects, not arrays.

The given tree [4,2,6,1,3,5,7] is represented by the following diagram:

          4
        /   \
      2      6
     / \    / \
    1   3  5   7

while the diagrams for the outputs are:

          4
        /   \
      3      6      and    2
            / \           /
           5   7         1
Note:
The size of the BST will not exceed 50.
The BST is always valid and each node's value is different.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;

    TreeNode(int data) : data(data), left(NULL), right(NULL) {}
};

vector<TreeNode *> splitBST(TreeNode *root, int val) {  //O(h)
    if (!root) return {NULL, NULL};
    vector<TreeNode *> res(2, NULL);  //{less,greater}

    if (root->data <= val) {
        res = splitBST(root->right, val);
        root->right = res[0];
        res[0] = root;
    } else {
        res = splitBST(root->left, val);
        root->left = res[1];
        res[1] = root;
    }

    return res;
}

int main() {
    return 0;
}

/*
Bottom-down traversal O (h) h is the tree height O (h) h is the tree height
Define a recursive function dfs that returns a two-dimensional array ans. After the current node and the left and right subtrees are divided by V, ans [0] is the part less than or equal to V, and ans [1] is the part greater than V.

If the current node node is greater than V, then ans [1] = node, and recursively call dfs on the left subtree of node to get the split result of the left subtree of the current node (a two-dimensional array of nodes). The left subtree of the current node is set to nodes [1], and ans [0] is set to nodes [0]

If the current node node is less than or equal to V, then ans [0] = node, and recursively call dfs on the right subtree of node to get the split result of the current subtree (a two-dimensional array of nodes). The right subtree of the current node is set to nodes [0], and ans [1] is set to nodes [1]

Time complexity analysis: each time select the recursive left subtree or right subtree according to the value of the current node, the time complexity is the tree height O (h)
*/