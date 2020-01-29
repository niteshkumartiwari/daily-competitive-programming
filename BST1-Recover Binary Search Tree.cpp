/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Example 1:

Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2
Example 2:

Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
Follow up:

A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?
*/

#include<bits/stdc++.h>
using namespace std;    

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    TreeNode *firstElem=NULL,*secondElem=NULL;
    TreeNode *prevElem = new TreeNode(INT_MIN);
public:
    void inorder(TreeNode *root){
        if(!root) return;
        inorder(root->left);

        if(firstElem==NULL && prevElem->val >= root->val)
            firstElem=prevElem;
        if(firstElem!=NULL && prevElem->val >= root->val)
            secondElem=root;
        prevElem=root;
        inorder(root->right);
    }
    void recoverTree(TreeNode* root) {
        inorder(root);

        int temp=firstElem->val;
        firstElem->val=secondElem->val;
        secondElem->val=temp;
    }
};


int main(){
   

    return 0;
}