/*
A Game of Queries
Problem Description

You are given an array A of numbers, which is circular and an array B of size M X 3, having operations as follows.

If B[i][0] is not equal to 2, increase all numbers in the segment [ B[i][1], B[i][2] ] by B[i][0] .

If B[i][0] = 2, calculate the minimum of the array in given range inclusive of both B[i][1] and B[i][2] .

Return an array of answers to the Type 2 queries.

Assuming circular segments, if we consider 5 elements and the segment [3, 1], we refer to index sequence [3, 4, 0, 1].



Problem Constraints
1 <= |A| <= 100000

1 <= |B| <= 100000

1 <= A[i] <= 500

It is assured that after any operation, all the numbers will fit into 32 bit integers.



Input Format
First argument is vector A.

Second argument is the vector of vectors B.



Output Format
Return an array, consisting of answers to the type 2 queries.



Example Input
Input 1:

 A = [2, 3, 4]
B = [    [1, 1, 2]
         [2, 3, 1]
    ]
Input 2:

A = [1, 2, 3]
B = [    [1, 3, 3]
         [2, 1, 3]
         [2, 1, 1]
    ]


Example Output
Output 1:

 [3]
Output 2:

 [1, 1]


Example Explanation
Explanation 1:

 After first operation, array is [3, 4, 4]. Now minimum across next range is 3.
Explanation 2:

 After first operation, array is [1, 2, 4]. Minimums can now be calculated.
*/
#include <bits/stdc++.h>

#include <unordered_map>
#include <unordered_set>
using namespace std;
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 400005
#define ll long long
const int MOD = 1e9 + 7;

/*----START CODING FROM HERE-------*/

//{first,second}=>{SCHEME,LAZY_COMPUTATION}
int tree[MAXSIZE];
int lazy[MAXSIZE];
int identity = INT_MAX;

void merge(int node) {
    //Merging the nodes after post order traversal
    //What SCHEME is needed to merge ??
    tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
}

void build(vector<int> &A, int node, int start, int end) {
    if (start == end) {
        tree[node] = A[start];
        return;
    }

    int mid = start + (end - start) / 2;
    build(A, 2 * node + 1, start, mid);
    build(A, 2 * node + 2, mid + 1, end);
    merge(node);
}

//push lazy computation to the child nodes
void push(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];  //increase the minimum
        if (start != end) {
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }
    }

    lazy[node] = 0;
}

int query(int node, int start, int end, int L, int R) {
    push(node, start, end);
    if (L <= start && end <= R)  //total overlap
        return tree[node];
    if (end < L || R < start)  //no overlap
        return identity;

    int mid = start + (end - start) / 2;
    return min(query(2 * node + 1, start, mid, L, R), query(2 * node + 2, mid + 1, end, L, R));
}

int update(int node, int start, int end, int L, int R, int K) {
    push(node, start, end);
    if (L <= start && end <= R) {  //total overlap
        lazy[node] += K;
        return tree[node] + K;
    }

    if (end < L || R < start)  //no overlap
        return tree[node];

    if (start != end) {
        int mid = (start + end) / 2;
        tree[node] = update(2 * node + 1, start, mid, L, R, K);
        tree[node] = min(tree[node], update(2 * node + 2, mid + 1, end, L, R, K));
    }

    return tree[node];
}

void initDS() {
    memset(tree, 0, sizeof tree);
    memset(lazy, 0, sizeof lazy);
}

vector<int> solve(vector<int> &A, vector<vector<int>> &B) {
    initDS();
    int n = A.size();
    build(A, 0, 0, n - 1);
    vector<int> res;

    for (auto q : B) {
        if (q[0] == 2) {  //query
            int L = q[1] - 1, R = q[2] - 1, val;

            if (L <= R)
                val = query(0, 0, n - 1, L, R);
            else {
                val = min(query(0, 0, n - 1, L, n - 1), query(0, 0, n - 1, 0, R));
            }
            res.push_back(val);
        } else {  //update
            int L = q[1] - 1, R = q[2] - 1;
            if (L <= R)
                update(0, 0, n - 1, L, R, q[0]);
            else {
                update(0, 0, n - 1, L, n - 1, q[0]);
                update(0, 0, n - 1, 0, R, q[0]);
            }
        }
    }

    return res;
}

int main() {
    // Solution sol= Solution();
    vector<int> A{4, 7, 2, 8, 9, 1, 2, 5};
    vector<vector<int>> B{
        {3, 7, 1},
        {2, 8, 2},
        {1, 3, 3},
        {2, 7, 3},
        {1, 4, 4},
        {2, 5, 4}};

    vector<int> res = solve(A, B);

    for (int val : res)
        cout << val << " ";

    return 0;
}
