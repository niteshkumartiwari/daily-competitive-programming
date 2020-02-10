/*
Given a binary tree and a leaf node from this tree. It is known that in 1s all nodes connected to a given node get’s burned. That is, left child, right child and parent. The task is to find the minimum time required to burn the complete binary tree.

Examples:

Input : 
            1
       /       \
      2          3
    /  \          \
   4    5          6
      /   \         \
     7     8         9
                      \
                       10
Leaf = 8
Output : 7
Initially 8 is set to fire at 0th sec.
            1
       /       \
      2          3
    /  \          \
   4    5          6
      /   \         \
     7     F         9
                      \
                       10
After 1s: 5 is set to fire.
            1
       /       \
      2          3
    /  \          \
   4    F          6
      /   \         \
     7     F         9
                      \
                       10
After 2s: 2, 7 are set to fire.
            1
       /       \
      F          3
    /  \          \
   4    F          6
      /   \         \
     F     F         9
                      \
                       10
After 3s: 4, 1 are set to fire.
            F
       /       \
      F          3
    /  \          \
   F    F          6
      /   \         \
     F     F         9
                      \
                       10
After 4s: 3 is set to fire.
            F
       /       \
      F          F
    /  \          \
   F    F          6
      /   \         \
     F     F         9
                      \
                       10
After 5s: 6 is set to fire.
            F
       /       \
      F          F
    /  \          \
   F    F          F
      /   \         \
     F     F         9
                      \
                       10
After 6s: 9 is set to fire.
            F
       /       \
      F          F
    /  \          \
   F    F          F
      /   \         \
     F     F         F
                      \
                       10
After 7s: 10 is set to fire.
            F
       /       \
      F          F
    /  \          \
   F    F          F
      /   \         \
     F     F         F
                      \
                       F
It takes 7s to burn the complete tree.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int data) : data(data), left(NULL), right(NULL);
};

struct Info {
    int lDepth;
    int rDepth;
    bool contains;
    int time;

    Info() {
        lDepth = rDepth = 0;
        contains = false;
        time = -1;
    }
};

Info calTime(Node *root, Info &info, int target, int &res) {
    if (!root) return info;

    if (root->data == target) {
        info.contains = true;
        info.time = 0;
        return info;
    }

    Info leftInfo;
    calTime(root->left, leftInfo, target, res);

    Info rightInfo;
    calTime(root->right, rightInfo, target, res);

    info.contains = (root->left && leftInfo.contains) || (root->right && rightInfo.contains);

    info.time = (root->left && leftInfo.contains) ? (leftInfo.time + 1) : -1;

    if (info.time == -1)
        info.time = (root->right && rightInfo.contains) ? (rightInfo.time + 1) : -1;

    info.lDepth = (root->left) ? (1 + max(leftInfo.lDepth, leftInfo.rDepth)) : 0;
    info.rDepth = (root->right) ? (1 + max(rightInfo.lDepth, rightInfo.rDepth)) : 0;

    if (info.contains) {
        if (root->left && leftInfo.contains)
            res = max(res, info.time + info.rDepth);
        else if (root->right && rightInfo.contains)
            res = max(res, info.time + info.lDepth);
    }
}

int maxTimeToBurn(Node *root, int target) {
    int res = 0;
    Info info;

    calTime(root, info, target, res);

    return res;
}

int main() {
    return 0;
}

/*
The idea is to store additional information for every node:

Depth of left subtree.
Depth of right subtree.
The time required for the fire to reach the current node starting from the first leaf node burned.
A boolean variable to check if the initial burnt node is in the tree rooted under current node.
Before moving ahead with the approach let’s take a look at the tree below:

              1
          /      \          
       2            3
     /   \         /
    4     5       6 
   /     / \
  8     9   10
       /
      11
In the above tree, if we set the leaf node 11 at fire.

In 1s, the fire will reach node 9.
In 2s, the fire will reach node 5.
In 3rd second, the fire will reach node 2 and 10. Here comes an observation:
In 2s fire reached node 5. For node 5, the initial burned leaf is in it’s left subtree, so the time taken to burn right subtree will be the height of the right subtree which is 1. Therefore, fire reaches to node 10 in (2+1) = 3s.
Again, for the node 2. Fire reached to node 2 in 3s from right subtree. Therefore, time taken to burn left subtree will be it’s height.
So the solution is to apply recursion and for every node calculate the below-required values:

Left Depth.
Right Depth.
The time required for fire to reach the current node.
Is the current subtree conatins initial burnt leaf node.
So, for the minimum time required to burn any subtree will be:

The time required for fire to reach the root node from initial burnt leaf + depth of the opposite side

Therefore, to find time required to burn the complete tree, we need to calculate the above value for every node, and take maximum of that value.

ans = max(ans, (time required for fire to reach current node + depth of other subtree))
*/
