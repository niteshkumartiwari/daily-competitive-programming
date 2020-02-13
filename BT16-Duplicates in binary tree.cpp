/*
Duplicates in binary tree
Given a binary tree of integers. Return whether it contains a duplicate sub-tree of size 2 or more. All node values lie between 0 and 9 inclusive. Return 1 if it contains a duplicate sub-tree of size 2 or more else return 0. Note: Two same leaf nodes are not considered as a subtree, As the size of a leaf node is one. Constraints
1 <= Number of nodes in binary tree <= 10000
0 <= node values <= 9
For Example
Input 1:
            1
          /   \
         2     6
        / \     \
       4   5     2
                / \
               4   5

Output 1:
    1

    Duplicate Subtree     2
                         / \
                        4   5

Input 2:
            1
           /  \
          2    3
           \
            4
             \
              5
Output 2:
    0
*/

#include<bits/stdc++.h>
using namespace std;   
typedef long long ll;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

unordered_set<string> us;
int res;

string serializeMe(TreeNode *A){
    if(!A) return "#";

    string val=""; 

    val+= to_string(A->val);
    val+= serializeMe(A->left);
    val+= serializeMe(A->right);
    

    if(val.length()>3 && us.count(val)!=0)
        res=1;
    
    us.insert(val);
    
    return val;
}

int solve(TreeNode* A) {
    us.clear();
    res=0;

    serializeMe(A);

    return res;
}


int main(){

    return 0;
}