/*
Construct a binary tree from a string consisting of parenthesis and integers. The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root’s value and a pair of parenthesis contains a child binary tree with the same structure. Always start to construct the left child node of the parent first if it exists.

Examples:

Input : "1(2)(3)" 
Output : 1 2 3
Explanation :
           1
          / \
         2   3
Explanation: first pair of parenthesis contains 
left subtree and second one contains the right 
subtree. Preorder of above tree is "1 2 3".  

Input : "4(2(3)(1))(6(5))"
Output : 4 2 3 1 6 5
Explanation :
           4
         /   \
        2     6
       / \   / 
      3   1 5   
We know first character in string is root. Substring inside the first adjacent pair of parenthesis is for left subtree and substring inside second pair of parenthesis is for right subtree as in the below diagram.

We need to find the substring corresponding to left subtree and substring corresponding to right subtree and then recursively call on both of the substrings.
For this first find the index of starting index and end index of each substring.
To find the index of closing parenthesis of left subtree substring, use a stack. Lets the found index is stored in index variable.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int data) : data(data), left(NULL), right(NULL);
};

int findMatchedBrac(string str, int si, int ei) {
    if (si > ei) return -1;

    stack<char> st;

    for (int i = si; i <= ei; i++) {
        if (str[i] == '(')
            st.push(str[i]);

        else if (str[i] == ')') {
            if (st.top() == '(')
                st.pop();

            if (st.empty())
                return i;
        }
    }

    return -1;
}

Node *treeFromString(string str, int si, int ei) {
    if (si > ei) return NULL;

    Node *root = new Node(str[si] - '0');
    int idx = -1;

    if (si + 1 < ei && str[si + 1] == '(')
        idx = findMatchedBrac(str, si + 1, ei);

    if (idx != -1) {
        root->left = treeFromString(str, si + 2, idx - 1);
        root->right = treeFromString(str, idx + 2, ei - 1);
    }

    return root;
}

int main() {
    return 0;
}
