/*
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    int i = 0;

   public:
    TreeNode* bstFromPreorder(vector<int>& preorder, int bound = INT_MAX) {
        if (i == preorder.size() || preorder[i] > bound) return NULL;
        TreeNode* root = new TreeNode(preorder[i++]);
        root->left = bstFromPreorder(preorder, root->val);
        root->right = bstFromPreorder(preorder, bound);
        return root;
    }
};

int main() {
    return 0;
}
