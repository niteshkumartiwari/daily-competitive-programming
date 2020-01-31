/*
Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree 
with largest number of nodes in it.
Note:
A subtree must include all of its descendants.
Here's an example:
    10
    / \
   5  15
  / \   \ 
 1   8   7
The Largest BST Subtree in this case is the highlighted one. 
The return value is the subtree's size, which is 3.
Hint:
You can recursively use algorithm similar to 98. Validate Binary Search Tree at each node of the tree, which will 
 result in O(nlogn) time complexity.
Follow up:
Can you figure out ways to solve it with O(n) time complexity?
*/

#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *left,*right;

    Node(int data){
        data=data;
        left=right=NULL;
    }
};

struct Info{
    int size;//size of subtree
    int max;//max value in subtree
    int min;//min value in subtree
    int ans;//size of largest BST subtree
    bool isBST;//if subtree is BST
};

Info largestBSTSubtree(Node *root){//O(n)
    if(!root) return {0,INT_MIN,INT_MAX,0,true};
    if(!root->left && !root->right) return {1,root->data,root->data,1,true};

    Info l= largestBSTSubtree(root->left);
    Info r= largestBSTSubtree(root->right);

    Info ret;

    ret.size=1+l.size+r.size;
    if(l.isBST && r.isBST && l.max < root->data && r.min > root->data){
        ret.min=min(l.min,root->data);
        ret.max=max(r.max,root->data);

        ret.ans=ret.size;
        ret.isBST=true;

        return ret;
    }

    ret.ans=max(l.size,r.size);
    ret.isBST=false;

    return ret;
}


int main(){
    struct Node *root = new Node(60); 
    root->left = new Node(65); 
    root->right = new Node(70); 
    root->left->left = new Node(50);

    cout<<largestBSTSubtree(root).ans;

    return 0;
}