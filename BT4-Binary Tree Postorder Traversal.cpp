/*
Given a binary tree, return the postorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
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

vector<int> postorderTraversal(TreeNode *root) {
    stack<TreeNode *> st;
    TreeNode *curr = root;
    vector<int> res;

    do {
        while (curr) {
            if (curr->right) st.push(curr->right);  //right-child exists
            st.push(curr);                          //push itself
            curr = curr->left;                      //move to left-most node
        }

        curr = st.top();
        st.pop();

        if (!st.empty() && curr->right == st.top()) {  //If right-child in on top of stack
            st.pop();                                  //take out right child
            st.push(curr);                             //push the data again for traversal
            curr = curr->right;
        } else {
            res.push_back(curr->val);
            curr = NULL;
        }
    } while (!st.empty());

    return res;
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    vector<int> res = postorderTraversal(root);

    for (int val : res)
        cout << val << " ";

    return 0;
}
