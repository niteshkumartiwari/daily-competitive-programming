/*
Given a non-empty binary search tree and a target value, find  k  values ​​in the BST that are closest to the target.
Note:
Given target value is a floating point.
You may assume  k  is always valid, that is:  k  ≤ total nodes.
You are guaranteed to have only one unique set of  k  values ​​in the BST that are closest to the target.
Follow up:
Assume that the BST is balanced, could you solve it in less than  O ( n ) runtime (where  n  = total nodes)?
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
There is also a method of O (logn), which uses two stacks to save the predecessor and successor of the target, and the top element of the stack stores the predecessor and successor closest to the target. The value closest to the target can be taken each time. This time complexity can reach O (logn). 
*/
struct TreeNode {
    int data;
    TreeNode *left, *right;

    TreeNode(int data) : data(data), left(NULL), right(NULL) {}
};

int getNextPredecessor(stack<TreeNode *> &st) {
    TreeNode *node = st.top();
    st.pop();
    TreeNode *next = node->left;

    while (next) {
        st.push(next);
        next = next->right;
    }

    return node->data;
}

int getNextSuccessor(stack<TreeNode *> &st) {
    TreeNode *node = st.top();
    st.pop();
    TreeNode *next = node->right;

    while (next) {
        st.push(next);
        next = next->left;
    }

    return node->data;
}

vector<int> closestKValues(TreeNode *root, double target, int k) {
    vector<int> result;

    stack<TreeNode *> predecessors, successors;

    while (!root) {
        if (root->data >= target) {
            successors.push(root);
            root = root->left;
        } else if (root->data < target) {
            predecessors.push(root);
            root = root->right;
        }
    }

    while (k > 0 && (!successors.empty() || !predecessors.empty())) {
        if (successors.empty())
            result.push_back(getNextPredecessor(predecessors));
        else if (predecessors.empty())
            result.push_back(getNextSuccessor(successors));
        else {
            if (abs(predecessors.top()->data - target) > abs(successors.top()->data - target))
                result.push_back(getNextSuccessor(successors));
            else
                result.push_back(getNextPredecessor(predecessors));
        }
        k--;
    }

    return result;
}

int main() {
    return 0;
}
