/*
Binary Lifting is a technique used to find the k-th ancestor of any node in a tree in O(logn). This also leads to a faster algorithm in finding the lowest common ancestor (LCA) between two nodes in a tree. It can also be used to compute functions such as minimum, maximum and sum between two nodes of a tree in logarithmic time. The technique requires preprocessing the tree in O(N log N) using dynamic programming.
The first step is to find out the 2j ancestor of every node where 0 <= j <= log(n). This can be done by dynamic programming.
The DP relation is given by:
    dp[i][j] = dp[dp[i][j-1]][j-1]
CCopy
Where dp[i][j] denotes the 2j th ancestor of the node i. The expression essentially breaks down the path between a node and its ancestor into two parts. The following figure illustrates this relation
binary_lifting
Note here that the fourth ancestor of Node 5 is the same as the second ancestor of Node 3.
To find the kth ancestor of a node, use the appropriate powers of two to sum up to the value k and move to the corresponding node in every step.
To find the LCA between two nodes a and b:
Find the node at the lowest level (let us say a, otherwise swap them)
Find the ancestor of a at the same level as b (let’s call this node c).
Find the lowest ancestors of b and c which are not equal.
Return the parent of one of the nodes found in step 3.
Pseudocode
The dp table can be computed by the following method:
	Precalculate():
		dp[i][j] = -1 for each pair i and j
for i = 1 to n
dp[i][0] = parent[i];
for h = 1 to logn
for i = 1 to n
If dp[i][h-1] not equal to -1
dp[i][h] = dp[dp[i][h-1]][h-1]
CCopy
The k’th ancestor can be calculated as follows
Findkthancestor():	
	//find kth ancestor of currentNode
	for i = logn to 0
		If dp[currentNode][i] != -1 and 2^i <= k:
			currentNode = dp[currentNode][2^i]
			k = k - 2^i
	return currentNode 
CCopy
The LCA between two nodes can be found as follows:
	FindLCA():
		//find lca between two nodes a and b
		If level[a] < level[b] 
			swap a and b
		c = a
		//find the ancestor of a at the same level of b
		for i = logn to 0
			If level[c] - 2^i >= level[b]
				c = dp[c][i]
		If b is equal to c
			return b
		for i = logn to 0
			If dp[b][i] != -1 and dp[b][i] != dp[c][i]
				b = dp[b][i]
				c = dp[c][i]
		return parent[b]
CCopy
Complexity
Preprocessing :
Best Case Complexity: O(N log N)
Average Case Complexity: O(N log N)
Worst Case Complexity: O(N log N)
Memory Complexity: O(N log N)
Find kth ancestor:
Best Case Complexity: O(log N)
Average Case Complexity: O(log N)
Worst Case Complexity: O(log N)
Memory Complexity: O(1) (Ignoring dp table)
Find LCA between two nodes:
Best Case Complexity: O(log N)
Average Case Complexity: O(log N)
Worst Case Complexity: O(log N)
Memory Complexity: O(1) (Ignoring dp table)
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define N 9

#define MAXLEVEL 5

void dfs(int u, vector<int> graph[], int depth,
         int parent[], int level[], int visited[]) {
    visited[u] = 1;
    level[u] = depth++;

    for (auto v : graph[u]) {
        if (!visited[v]) {
            visited[v] = true;
            parent[v] = u;
            dfs(v, graph, depth, parent, level, visited);
        }
    }
}

void precalculate(int dp[][MAXLEVEL], int parent[]) {
    for (int i = 0; i < N; i++)
        dp[i][0] = parent[i];

    for (int h = 1; h < MAXLEVEL; h++) {
        for (int i = 0; i < N; i++) {
            if (dp[i][h - 1] != -1)
                dp[i][h] = dp[dp[i][h - 1]][h - 1];
        }
    }
}

void findKth(int u, int k, int dp[][MAXLEVEL]) {
    for (int i = MAXLEVEL; i >= 0; i--) {
        if (dp[u][i] != -1 && (1 << i) <= k) {
            u = dp[u][i];
            k -= (1 << i);
        }
    }

    cout << "Ans is: " << u << endl;
}

void lca(int a, int b, int level[], int dp[][MAXLEVEL], int parent[]) {
    if (level[a] < level[b])
        swap(a, b);

    int l;
    for (l = 0; (1 << l) <= level[a]; l++)
        ;

    //find the ancestor of a who is at the same level of b
    for (int i = l - 1; i >= 0; i--) {
        if (level[a] - (1 << i) >= level[b])
            a = dp[a][i];
    }

    if (a == b) {
        cout << "The lowest common ancestor of a and b is " << a << '\n';
        return;
    }

    //find the lowest ancestor of a and b which are not equal
    for (int i = l; i >= 0; i--) {
        if (dp[a][i] != dp[b][i]) {
            a = dp[a][i];
            b = dp[b][i];
        }
    }

    cout << "The lowest common ancestor of a and b is " << parent[a] << '\n';
}

int main() {
    vector<int> graph[N];

    int parent[N], level[N], visited[N], dp[N][MAXLEVEL];

    memset(parent, 0, sizeof parent);
    memset(level, 0, sizeof level);
    memset(visited, 0, sizeof visited);

    memset(dp, -1, sizeof dp);

    /* create an undirected graph of the structure:
            0
          /   \
         1     2
        / \   / \
       3   4 5   6
            /     \
           7       8
    */

    graph[0].push_back(1);
    graph[1].push_back(0);
    graph[0].push_back(2);
    graph[2].push_back(0);
    graph[1].push_back(3);
    graph[3].push_back(1);
    graph[1].push_back(4);
    graph[4].push_back(1);
    graph[2].push_back(5);
    graph[5].push_back(2);
    graph[2].push_back(6);
    graph[6].push_back(2);
    graph[5].push_back(7);
    graph[7].push_back(5);
    graph[6].push_back(8);
    graph[8].push_back(6);

    int depth = 0;

    dfs(0, graph, depth, parent, level, visited);

    precalculate(dp, parent);

    findKth(3, 1, dp);

    lca(8, 7, level, dp, parent);

    return 0;
}

//Range Minimum Query with Euler Tour

vector<int> adj[100009];
vector<int> euler;
vector<int> level;
vector<int> depthArr;
vector<int> FO;
int maxDepth;
int dp[100009][20];
int ptr;

void dfs(int u, int depth) {  //O(N)
    if (FO[u] == -1) FO[u] = ptr;
    level[u] = depth;
    euler.push_back(u);
    ptr++;
    maxDepth = max(maxDepth, depth);

    for (auto v : adj[u]) {
        dfs(v, depth + 1);
        euler.push_back(u);
        ptr++;
    }
}

void preprocessing() {  //O(NlogN)
    int n = euler.size();
    memset(dp, -1, sizeof dp);
    //dp[i][j]:= idx of lca between i to 2^j= with depthArr min between [i,j]

    for (int x : euler)
        depthArr.push_back(level[x]);

    for (int i = 1; i < n; i++)
        dp[i - 1][0] = (depthArr[i] > depthArr[i - 1]) ? i - 1 : i;

    for (int l = 1; l < 20; l++) {
        for (int i = 0; i < n; i++) {
            if (dp[i][l - 1] != -1 && dp[i + (1 << (l - 1))][l - 1] != -1)
                dp[i][l] = (depthArr[dp[i][l - 1]] > depthArr[dp[i + (1 << (l - 1))][l - 1]]) ? dp[i + (1 << (l - 1))][l - 1] : dp[i][l - 1];
            else
                break;
        }
    }
}

int query(int l, int r) {
    int d = r - l;
    int dx = log2(d);

    if (l == r) return l;

    if (depthArr[dp[l][dx]] > depthArr[dp[r - (1 << dx)][dx]])
        return dp[r - (1 << dx)][dx];
    else
        return dp[l][dx];
}

int LCA(int u, int v) {
    if (u == v) return u;
    if (FO[u] > FO[v]) swap(u, v);

    return euler[query(FO[u], FO[v])];
}

void setDS() {
    euler.clear();
    depthArr.clear();
    level.clear();
    FO.clear();

    level.resize(100009, 0);
    FO.resize(100009, -1);
    maxDepth = 0;
    ptr = 0;

    for (int i = 0; i < 100009; i++)
        adj[i].clear();
}

int solve(vector<int>& A, vector<int>& B) {
    setDS();

    for (int i = 0; i < A.size(); i++)
        adj[A[i]].push_back(i + 1);

    dfs(0, 0);

    preprocessing();

    int lca = B[0];
    for (int i = 1; i < B.size(); i++)
        lca = LCA(lca, B[i]);

    return lca;
}