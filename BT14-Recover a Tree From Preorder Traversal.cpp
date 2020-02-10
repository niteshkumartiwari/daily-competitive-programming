/*
We run a preorder depth first search on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

If a node has only one child, that child is guaranteed to be the left child.

Given the output S of this traversal, recover the tree and return its root.
*/

#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {  //logic is correct code nt working
   public:
    TreeNode *recoverFromPreorder(string S) {
        int n = S.length();
        stack<TreeNode *> st;

        for (int i = 0; i < S.length();) {
            int level = 0;
            for (; S[i] == '-'; i++)
                level++;
            int val = 0;
            for (int i = 0; i < S.length() && S[i] != '-'; i++)
                val = 10 * val + (S[i] - '0');

            TreeNode *node = new TreeNode(val);
            while (st.size() > level) st.pop();
            if (!st.top()->left)
                st.top()->left = node;
            else
                st.top()->right = node;
            st.push(node);
        }

        while (st.size() > 1) st.pop();

        return st.top();
    }
};

int main() {
    return 0;
}
