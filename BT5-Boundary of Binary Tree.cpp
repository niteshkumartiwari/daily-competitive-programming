/*
Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root. Boundary includes left boundary, leaves, and right boundary in order without duplicate nodes.
Left boundary is defined as the path from root to the left-most node. Right boundary is defined as the path from root to the right-most node. If the root doesn't have left subtree or right subtree, then the root itself is left boundary or right boundary. Note this definition only applies to the input binary tree, and not applies to any subtrees.
The left-most node is defined as a leaf node you could reach when you always firstly travel to the left subtree if exists. If not, travel to the right subtree. Repeat until you reach a leaf node.
The right-most node is also defined by the same way with left and right exchanged.
Example 1
Input:
  1
   \
    2
   / \
  3   4

Ouput:
[1, 3, 4, 2]

Explanation:
The root doesn't have left subtree, so the root itself is left boundary.
The leaves are node 3 and 4.
The right boundary are node 1,2,4. Note the anti-clockwise direction means you should output reversed right boundary.
So order them in anti-clockwise without duplicates and we have [1,3,4,2].

Example 2
Input:
    ____1_____
   /          \
  2            3
 / \          / 
4   5        6   
   / \      / \
  7   8    9  10  
       
Ouput:
[1,2,4,7,8,9,10,6,3]

Explanation:
The left boundary are node 1,2,4. (4 is the left-most node according to definition)
The leaves are node 4,7,8,9,10.
The right boundary are node 1,3,6,10. (10 is the right-most node).
So order them in anti-clockwise without duplicate nodes we have [1,2,4,7,8,9,10,6,3].
*/

#include<bits/stdc++.h>
using namespace std;    
/*
We break the problem in 3 parts:
1. Print the left boundary in top-down manner.
2. Print all leaf nodes from left to right, which can again be sub-divided into two sub-parts:
…..2.1 Print all leaf nodes of left sub-tree from left to right.
…..2.2 Print all leaf nodes of right subtree from left to right.
3. Print the right boundary in bottom-up manner.
*/

//O(n) where n is the number of nodes in binary tree.


struct Node{
    int data;
    Node *left,*right;
};


void printLeftBoundary(Node *root){
    if(!root) return;

    if(root->left){
        // to ensure top down order, print the node 
        // before calling itself for left subtree 
        cout<<root->data<<" ";
        printLeftBoundary(root->left);
    }
    else if(root->right){
        cout<<root->data<<" ";
        printLeftBoundary(root->right);
    }
    // do nothing if it is a leaf node, this way we avoid 
    // duplicates in output
}

void printRightBoundary(Node *root){
    if(!root) return;

    if(root->right){
        // to ensure bottom up order, first call for right 
        // subtree, then print this node 
        printRightBoundary(root->right);
        cout<<root->data<<" ";
    }
    else if(root->left){
        printRightBoundary(root->left);
        cout<<root->data<<" ";
    }
    // do nothing if it is a leaf node, this way we avoid 
    // duplicates in output 
}

void printLeaves(Node *root){
    if(!root) return;
    printLeaves(root->left);

    //print it if its leaf node 
    if(!root->left && !root->right)
        cout<<root->data<<" ";

    printLeaves(root->right);
}

void printBoundary(Node *root){
    if(!root) return;

    cout<<root->data<<" ";

    // Print the left boundary in top-down manner.
    printLeftBoundary(root->left);

    // Print all leaf nodes 
    printLeaves(root->left);
    printLeaves(root->right);

    // Print the right boundary in bottom-up manner 
    printRightBoundary(root->right);
}

int main(){
   

    return 0;
}