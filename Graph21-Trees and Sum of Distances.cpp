
/*
An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.

The ith edge connects nodes A[i][0] and A[i][1] together.

Return an array of integers, ith index representes the sum of the distances between node i and all other nodes.



Input Format:

The first and the only argument has a 2-d array of integers of size N x 2, where nodes A[i][0] and A[i][1] are connected.
Output Format:

Return an array of integers, where the ith index represents the answer as described in the problem statement.
Constraints

1 <= A <= 10000
For Example:

Input 1:
    A = [[3, 1], [2, 1], [0, 2], [3, 4]]

Output 1:
    [10, 6, 7, 7, 10]

Explanation 1:
    dist(0, 1) = 2
    dist(0, 2) = 1
    dist(0, 3) = 3
    dist(0, 4) = 4

    Total sum of distances for Node 0 : 1 + 2 + 3 + 4 = 10.
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 10004
const int MOD = 1e9 + 7;

/*----START CODING FROM HERE-------*/

vector<int> adj[MAXSIZE];  //graph
vector<int> dist;          //distance of all nodes from i
vector<int> count1;        //size of subtree rooted at i
int N;
void postOrder(int u, int parent) {
    for (auto v : adj[u]) {
        if (v == parent) continue;
        postOrder(v, u);
        count1[u] += count1[v];
        dist[u] += dist[v] + count1[v];  //because all nodes are +1 far from u as from v
    }
    count1[u]++;  //count1ing itself
}

void preOrder(int u, int parent) {
    for (auto v : adj[u]) {
        if (v == parent) continue;
        dist[v] = dist[u] - count1[v] + N - count1[v];

        preOrder(v, u);
    }
}

vector<int> solve(vector<vector<int>> &A) {
    N = 0;
    for (int i = 0; i < MAXSIZE; i++) adj[i].clear();

    for (auto a : A) {
        N = max({N, a[0], a[1]});
        adj[a[0]].push_back(a[1]);
        adj[a[1]].push_back(a[0]);
    }

    N += 1;
    dist.resize(N, 0);
    count1.resize(N, 0);

    postOrder(0, -1);
    preOrder(0, -1);

    return dist;
}

int main() {
    vector<vector<int>> A{
        {2, 1},
        {2, 0},
        {3, 2},
        {4, 3}};

    vector<int> res = solve(A);

    for (int val : res)
        cout << val << " ";

    return 0;
}

//Explanation

/*
Intuition
What if given a tree, with a certain root 0?
In O(N) we can find sum of distances in tree from root and all other nodes.
Now for all N nodes?
Of course, we can do it N times and solve it in O(N^2).
C++ and Java may get accepted luckily, but it's not what we want.

When we move our root from one node to its connected node,
one part of nodes get closer, one the other part get further.

If we know exactly how many nodes in both parts, we can solve this problem.

With one single traversal in tree, we should get enough information for it and
don't need to do it again and again.


Explanation
Let's solve it with node 0 as root.

Initial an array of hashset tree, tree[i] contains all connected nodes to i.
Initial an array count, count[i] counts all nodes in the subtree i.
Initial an array of res, res[i] counts sum of distance in subtree i.

Post order dfs traversal, update count and res:
count[root] = sum(count[i]) + 1
res[root] = sum(res[i]) + sum(count[i])

Pre order dfs traversal, update res:
When we move our root from parent to its child i, count[i] points get 1 closer to root, n - count[i] nodes get 1 futhur to root.
res[i] = res[root] - count[i] + N - count[i]

return res, done.


Time Complexity:
dfs: O(N) time
dfs2: O(N) time
*/