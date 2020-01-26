/*
Input 1:
            1
          /   \
         2    3
        / \  / \
       4   5 6  7
      /
     8 

     B = 3
     C = 3
Output 1:
    [4, 5]

Input 2:
            1
           /  \
          2    3
           \
            4
             \
              5
        B = 4
        C = 1
Output 2:
    [2, 5]
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

void CdistanceDown(TreeNode *A, int C, vector<int> &res) {
    if (!A) return;
    if (C == 0) {
        res.push_back(A->val);
        return;
    }
    CdistanceDown(A->left, C - 1, res);
    CdistanceDown(A->right, C - 1, res);
}

int solveUtil(TreeNode *A, int B, int C, vector<int> &res) {
    if (!A) return -1;

    if (A->val == B) {
        CdistanceDown(A, C, res);
        return 0;
    }

    int l = solveUtil(A->left, B, C, res);

    if (l != -1) {  //val is in the left-subtree
        if (l + 1 == C)
            res.push_back(A->val);
        else
            CdistanceDown(A->right, C - l - 2, res);  //CHECK ME
        return l + 1;                                 //curr node is l+1 away from target node
    }

    int r = solveUtil(A->right, B, C, res);

    if (r != -1) {
        if (r + 1 == C)
            res.push_back(A->val);
        else
            CdistanceDown(A->left, C - r - 2, res);
        return r + 1;
    }

    return -1;  //doesn't exist in this subtree
}

vector<int> solve(TreeNode *A, int B, int C) {
    vector<int> res;
    solveUtil(A, B, C, res);

    return res;
}

int main() {
    return 0;
}

/*
Time Complexity: At first look the time complexity looks more than O(n), but if we take a closer look, we can observe that no node is traversed more than twice. Therefore the time complexity is O(n).
*/