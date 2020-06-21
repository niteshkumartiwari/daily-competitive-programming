/*
Problem Description

You are given an array A of size N consisting of integers.

You have to process Q queries of two types on it:

i x, change the i-th element of A to x.
l r, find the maximum value of (A[i]+A[i+1]...A[j]) over all pairs (i,j) such that l <= i <= j <= r.


Problem Constraints
1 <= N,Q <= 105
-1000 <= A[i] <= 1000 (for all i in [1...N])
For query of the 1st type,

1 <= i <= N
-1000 <= x <= 1000
For query of the 2nd type,

1 <= l <= r <= N


Input Format
The first argument of the input is the array A.

The second argument of the input is a 2-D array B containing the description of the queries.



Output Format
You should return an array of answers to each query of the 2nd type, in the same order they were asked in the input.



Example Input
Input 1:

A: [3, -1, 2, -9, -15]

B: [
        [2,1,4],
        [1,3,7],
        [2,5,5],
        [2,1,3]
    ]
Input 2:

A: [6, -1, 9]

B:  [
        [2,1,3],
        [1,2,10],
        [2,1,3]
    ]


Example Output
Output 1:

[4, -15, 9]
Output 2:

[14, 25]


Example Explanation
Explanation 1:


For the 1st query, the required sum is A[1] + A[2] + A[3] = 4

After the 2nd query, array becomes [3,-1,7,-9,-15].

For the 3rd query, there is only one answer possible, -15, which is thus the answer itself.

For the 4th query, the required sum is A[1] + A[2] + A[3] = 9.


Explanation 2:


For the 1st query, the required sum is A[1] + A[2] + A[3] = 14

After the 2nd query, array becomes [6, 10, 9].

For the 3rd query, the required sum is A[1] + A[2] + A[3] = 14
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

//MyCode erroneous...look bootom code for working one

#define MAXSIZE 1001
vector<int> segmentTree[4 * MAXSIZE];

vector<int> getResult(int ss, int se, int qs, int qe, int sIdx) {
    //no-overlap
    if (qs > se || qe < ss)
        return {INT_MIN, INT_MIN, INT_MIN, INT_MIN};

    //complete-overlap
    if (qs <= ss && qe >= se)
        return segmentTree[sIdx];

    int m = ss + (se - ss) / 2;
    if (qe <= m)
        return getResult(ss, m, qs, qe, 2 * sIdx);
    if (qs > m)
        return getResult(m + 1, se, qs, qe, 2 * sIdx + 1);

    vector<int> lVal = getResult(ss, m, qs, qe, 2 * sIdx);
    vector<int> rVal = getResult(m + 1, se, qs, qe, 2 * sIdx + 1);

    int mPrefix = max(lVal[0], lVal[3] + rVal[0]);
    int mSuffix = max(rVal[1], rVal[3] + lVal[1]);
    int mTotSum = lVal[3] + rVal[3];
    int mMaxSum = max({mPrefix, mSuffix, lVal[2], rVal[2], lVal[1] + rVal[0]});
    return segmentTree[sIdx] = {mPrefix, mSuffix, mMaxSum, mTotSum};
}

vector<int> update(int aIdx, int ss, int se, int val, int sIdx) {
    if (aIdx < ss || aIdx > se) return {0, 0, 0, 0};

    if (ss == se) {
        return segmentTree[sIdx] = {val, val, val, val};
    }

    int m = ss + (se - ss) / 2;
    if (aIdx <= m)
        update(aIdx, ss, m, val, 2 * sIdx);
    else
        update(aIdx, m + 1, se, val, 2 * sIdx + 1);

    vector<int> lVal = segmentTree[2 * sIdx];
    vector<int> rVal = segmentTree[2 * sIdx + 1];

    int mPrefix = max(lVal[0], lVal[3] + rVal[0]);
    int mSuffix = max(rVal[1], rVal[3] + lVal[1]);
    int mTotSum = lVal[3] + rVal[3];
    int mMaxSum = max({mPrefix, mSuffix, lVal[2], rVal[2], lVal[1] + rVal[0]});
    return segmentTree[sIdx] = {mPrefix, mSuffix, mMaxSum, mTotSum};
}

vector<int> build(vector<int> &arr, int l, int r, int sIdx) {
    //prefix,suffix,maxsum,totsum
    if (l == r) {
        return segmentTree[sIdx] = {arr[l - 1], arr[l - 1], arr[l - 1], arr[l - 1]};
    }

    int m = l + (r - l) / 2;

    vector<int> lVal = build(arr, l, m, 2 * sIdx);
    vector<int> rVal = build(arr, m + 1, r, 2 * sIdx + 1);

    int mPrefix = max(lVal[0], lVal[3] + rVal[0]);
    int mSuffix = max(rVal[1], rVal[3] + lVal[1]);
    int mTotSum = lVal[3] + rVal[3];
    int mMaxSum = max({mPrefix, mSuffix, lVal[2], rVal[2], lVal[1] + rVal[0]});
    return segmentTree[sIdx] = {mPrefix, mSuffix, mMaxSum, mTotSum};
}

vector<int> Solution::solve(vector<int> &arr, vector<vector<int> > &queries) {
    for (int i = 0; i < 4 * MAXSIZE; i++)
        segmentTree[i].clear();

    int n = arr.size();

    build(arr, 1, n, 1);
    vector<int> res;

    for (auto query : queries) {
        if (query[0] == 1) {
            //Update Query
            arr[query[1] - 1] = query[2];
            update(query[1], 1, n, query[2], 1);
        } else {
            res.push_back(getResult(1, n, query[1], query[2], 1)[2]);
        }
    }

    return res;
}

//============================WORKING====================================

// CPP program to find Largest Sum Contiguous
// Subarray in a given range with updates
#include <bits/stdc++.h>
using namespace std;

// Structure to store
// 4 values that are to be stored
// in the nodes
struct node {
    int sum, prefixsum, suffixsum, maxsum;
};

// array to store the segment tree
node tree[4 * 100];

// function to build the tree
void build(int arr[], int low, int high, int index) {
    // the leaf node
    if (low == high) {
        tree[index].sum = arr[low];
        tree[index].prefixsum = arr[low];
        tree[index].suffixsum = arr[low];
        tree[index].maxsum = arr[low];
    } else {
        int mid = (low + high) / 2;

        // left subtree
        build(arr, low, mid, 2 * index + 1);

        // right subtree
        build(arr, mid + 1, high, 2 * index + 2);

        // parent node's sum is the summation
        // of left and right child
        tree[index].sum = tree[2 * index + 1].sum +
                          tree[2 * index + 2].sum;

        // parent node's prefix sum will be equivalent
        // to maximum of left child's prefix sum or left
        // child sum + right child prefix sum.
        tree[index].prefixsum =
            max(tree[2 * index + 1].prefixsum,
                tree[2 * index + 1].sum +
                    tree[2 * index + 2].prefixsum);

        // parent node's suffix sum will be equal to right
        // child suffix sum or right child sum + suffix
        // sum of left child
        tree[index].suffixsum =
            max(tree[2 * index + 2].suffixsum,
                tree[2 * index + 2].sum +
                    tree[2 * index + 1].suffixsum);

        // maxum will be the maximum of prefix, suffix of
        // parent or maximum of left child or right child
        // and summation of left child's suffix and right
        // child's prefix.
        tree[index].maxsum =
            max(tree[index].prefixsum,
                max(tree[index].suffixsum,
                    max(tree[2 * index + 1].maxsum,
                        max(tree[2 * index + 2].maxsum,
                            tree[2 * index + 1].suffixsum +
                                tree[2 * index + 2].prefixsum))));
    }
}

// function to update the tree
void update(int arr[], int index, int low, int high,
            int idx, int value) {
    // the node to be updated
    if (low == high) {
        tree[index].sum = value;
        tree[index].prefixsum = value;
        tree[index].suffixsum = value;
        tree[index].maxsum = value;
    } else {
        int mid = (low + high) / 2;

        // if node to be updated is in left subtree
        if (idx <= mid)
            update(arr, 2 * index + 1, low, mid, idx, value);

        // if node to be updated is in right subtree
        else
            update(arr, 2 * index + 2, mid + 1,
                   high, idx, value);

        // parent node's sum is the summation of left
        // and right child
        tree[index].sum = tree[2 * index + 1].sum +
                          tree[2 * index + 2].sum;

        // parent node's prefix sum will be equivalent
        // to maximum of left child's prefix sum or left
        // child sum + right child prefix sum.
        tree[index].prefixsum =
            max(tree[2 * index + 1].prefixsum,
                tree[2 * index + 1].sum +
                    tree[2 * index + 2].prefixsum);

        // parent node's suffix sum will be equal to right
        // child suffix sum or right child sum + suffix
        // sum of left child
        tree[index].suffixsum =
            max(tree[2 * index + 2].suffixsum,
                tree[2 * index + 2].sum +
                    tree[2 * index + 1].suffixsum);

        // maxum will be the maximum of prefix, suffix of
        // parent or maximum of left child or right child
        // and summation of left child's suffix and
        // right child's prefix.
        tree[index].maxsum =
            max(tree[index].prefixsum,
                max(tree[index].suffixsum,
                    max(tree[2 * index + 1].maxsum,
                        max(tree[2 * index + 2].maxsum,
                            tree[2 * index + 1].suffixsum +
                                tree[2 * index + 2].prefixsum))));
    }
}

// fucntion to return answer to every type-1 query
node query(int arr[], int index, int low,
           int high, int l, int r) {
    // initially all the values are INT_MIN
    node result;
    result.sum = result.prefixsum =
        result.suffixsum =
            result.maxsum = INT_MIN;

    // range does not lies in this subtree
    if (r < low || high < l)
        return result;

    // complete overlap of range
    if (l <= low && high <= r)
        return tree[index];

    int mid = (low + high) / 2;

    // right subtree
    if (l > mid)
        return query(arr, 2 * index + 2,
                     mid + 1, high, l, r);

    // left subtree
    if (r <= mid)
        return query(arr, 2 * index + 1,
                     low, mid, l, r);

    node left = query(arr, 2 * index + 1,
                      low, mid, l, r);
    node right = query(arr, 2 * index + 2,
                       mid + 1, high, l, r);

    // finding the maximum and returning it
    result.sum = left.sum + right.sum;
    result.prefixsum = max(left.prefixsum, left.sum +
                                               right.prefixsum);

    result.suffixsum = max(right.suffixsum,
                           right.sum + left.suffixsum);
    result.maxsum = max(result.prefixsum,
                        max(result.suffixsum,
                            max(left.maxsum,
                                max(right.maxsum,
                                    left.suffixsum + right.prefixsum))));

    return result;
}

// Driver Code
int main() {
    int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(a) / sizeof(a[0]);

    // build the tree
    build(a, 0, n - 1, 0);

    // 1st query type-1
    int l = 5, r = 8;
    cout << query(a, 0, 0, n - 1, l - 1, r - 1).maxsum;
    cout << endl;

    // 2nd type-2 query
    int index = 1;
    int value = 10;
    a[index - 1] = value;
    update(a, 0, 0, n - 1, index - 1, value);

    // 3rd type-1 query
    l = 1, r = 3;
    cout << query(a, 0, 0, n - 1, l - 1, r - 1).maxsum;

    return 0;
}

int main() {
    return 0;
}
