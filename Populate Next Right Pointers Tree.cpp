/*
Given the following binary tree,

               1
              /  \
            2     3
           /  \     /  \
           4    5   6   7


Example Output
             1 -> NULL
           /  \
          2 -> 3 -> NULL
        /  \  /  \
        4->5->6->7->NULL
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct TreeLinkNode {
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
};

TreeLinkNode *getRightNext(TreeLinkNode *A) {
    while (A) {
        if (A->left)
            return A->left;
        if (A->right)
            return A->right;
        A = A->next;
    }

    return A;
}

void connect(TreeLinkNode *A) {
    TreeLinkNode *p = A;
    p->next = NULL;

    while (p) {
        TreeLinkNode *q = p;

        while (q) {
            if (q->left) {
                if (q->right)
                    q->left->next = q->right;
                else
                    q->left->next = getRightNext(q->next);
            }

            if (q->right)
                q->right->next = getRightNext(q->next);

            q = q->next;
        }

        if (p->left)
            p = p->left;
        else if (p->right)
            p = p->right;
        else
            p = getRightNext(p->next);
    }
}

int main() {
    return 0;
}
