/*
Problem Description

Given a Linked list A of length N, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list.

NOTE:

If thery are mutiple consecutive sequences to delete then the sequence which occurs first will be deleted first and so on.



Problem Constraints
1 <= N <= 105

-103 <= Value in Each Link List <= 103



Input Format
First argument is the head pointer of the linkedlist.



Output Format
Return the head pointer of the final linkedlist as described.



Example Input
Input 1:

 3 -> 4 -> -7 -> 5 -> -6 -> 6
Input 2:

 1 -> 4 -> 6 -> -6 -> -4 -> 10
Input 3:

 1 -> -1


Example Output
Output 1:

 5
Output 2:

 1 -> 10
Output 3:

 


Example Explanation
Explanation 1:

 You first remove 3 -> 4 -> -7 and then -6 -> 6 leaving only 1
Explanation 2:

 There can be multiple answers like:
    If we delete 4 -> 6 -> -6 -> -4 then we get 1 -> 10 as the answer.
    If we delete -6 -> -4 -> 10 we get 1 -> 4 -> 6 as the answer.

    But in question it is given that delete the sequence which occurs first 
    so 4 -> 6 -> -6 -> -4 occurs first so we will remove it  and output will be 1 -> 10.
Explanation 3:

 Removing 1 -> -1 as it sums to zero. We will return a empty linked list.

*/

#include <bits/stdc++.h>

#include <unordered_map>
#include <unordered_set>
using namespace std;
#define ll long long
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 100005
const int MOD = 1e9 + 7;

/*----START CODING FROM HERE-------*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *solve(ListNode *A) {
    ListNode *root = new ListNode(0);
    root->next = A;
    unordered_map<int, ListNode *> um;
    um[0] = root;
    int sum = 0;

    while (A) {
        sum += A->val;

        if (um.count(sum) != 0) {
            ListNode *prev = um[sum];
            ListNode *start = prev;

            int currSum = sum;
            while (prev != A) {
                prev = prev->next;
                currSum += prev->val;
                if (prev != A) um.erase(currSum);
            }

            start->next = A->next;
        } else
            um[sum] = A;

        A = A->next;
    }

    return root->next;
}

int main() {
    ListNode *head = new ListNode(1);
    head->next = new ListNode(4);
    head->next->next = new ListNode(6);
    head->next->next->next = new ListNode(-6);
    head->next->next->next->next = new ListNode(-4);
    head->next->next->next->next->next = new ListNode(10);

    ListNode *res = solve(head);

    while (res) {
        cout << res->val << " ";
        res = res->next;
    }

    return 0;
}

/*
Iterate LinkedList from left to right
Process each accumulative value in this datastructure. (unordered_map<int,ListNode*>um) um[ac] = currentNode;
Given a current accumulative value check if exists in our map (get previous element).
If they exist um[ac]->next = currentNode->next, then delete intermediate nodes in our map between um[ac] and currentNode
*/