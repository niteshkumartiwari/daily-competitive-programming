/*
Problem Description

Given a tree with N nodes numbered from 1 to N.

Each node has a lowercase character associated with it.

You are given Q queries, in each query you are given two integers u and v and you are required to find the character with a minimum non-zero frequency in a simple path from u to v.

NOTE:

If there is more than one character with minimum frequency, then output the lexographically smallest character.
Each edge in the tree is bi-directional.


Problem Constraints
2 <= N, Q <= 105

1 <= u, v <= N and u != v



Input Format
First argument is an character array A of size N denoting character assigned to each nodes.

Second argument is a 2-D array B of size (N-1) x 2 denoting the edge of the tree.

Third argument is a 2-D array C of size Q x 2 denoting the queries, C[i][0] denotes u and C[i][1] denotes v.



Output Format
Return a string of size Q denoting answer for each query.



Example Input
Input 1:

 A = ['a', 'a', 'b']
 B = [ 
        [1, 2]
        [2, 3]
     ]
 C = [
        [1, 3]
        [2, 3]
     ]
Input 2:

 A = ['a', 'b']
 B = [
        [1, 2]
     ]
 C = [
        [1, 2]
        [2, 1]
     ]


Example Output
Output 1:

 "ba"
Output 2:

 "aa"


Example Explanation
Explanation 1:

 For Query 1: u = 1 and v = 3 so the path from 1 to 3 is 1 -> 2 -> 3 , 'a' occurs for two times on this path and 'b' occurs once.
 So 'b' will be the minimum frequency character in the path from 1 to 3.

 For Query 2: u = 2 and v = 3 so the path from 2 to 3 is 2 -> 3 , 'a' and 'b' each occurs once on this path.
 As both 'a' and 'b' are the minimum frequency character so we will output the lexographically smallest one i.e 'a'.
Explanation 2:

 For Query 1: u = 1 and v = 2 so the path from 1 to 2 us 1 -> 2 , 'a' and 'b' occurs once on this path.
 As both 'a' and 'b' are the minimum frequency character so we will output the lexographically smallest one i.e 'a'.

 Query 2 is same as Query 1.
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

#include <bits/stdc++.h>

#include <unordered_map>
#include <unordered_set>
using namespace std;
#define pii pair<int, pair<int, int>>
#define pi pair<int, int>
#define MAXSIZE 100005
#define ll long long
const int MOD = 1e9 + 7;

/*----START CODING FROM HERE-------*/
vector<int> adj[MAXSIZE];
vector<int> height;
vector<int> parentNode;
vector<vector<int>> dp;
vector<vector<int>> freq;
int maxHeight;

//sparse table and Binary-Lifting
//dp[i][j]:= node which is 2^j from i
void dfs(vector<char>& A, int x, int parent) {
    height[x] = height[parent] + 1;
    parentNode[x] = parent;
    dp[x][0] = parent;
    maxHeight = max(maxHeight, height[x]);

    for (int i = 0; i < 26; i++)
        freq[x][i] += freq[parent][i];
    char curr = A[x - 1];
    freq[x][curr - 'a']++;

    for (int child : adj[x]) {
        if (child == parent) continue;
        dfs(A, child, x);
    }
}

void buildSparseTable(vector<char> A) {
    int n = A.size();
    for (int j = 1; j <= log2(maxHeight); j++) {
        for (int i = 1; i <= n; i++)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
}

int getLCA(int u, int v) {
    //make sure height of u is always greater
    if (height[u] < height[v])
        swap(u, v);

    //get u & v at same level
    int diff = height[u] - height[v];
    for (int i = log2(diff); i >= 0; i--) {
        diff = height[u] - height[v];
        if (height[u] == height[v]) break;
        if (diff - (1 << i) >= 0)
            u = dp[u][i];
    }

    if (u == v) return u;

    //binary lifting
    for (int i = log2(maxHeight); i >= 0; i--) {
        if (dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }

    return dp[u][0];
}

string solve(vector<char>& A, vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();

    //initializing
    for (int i = 0; i < MAXSIZE; i++)
        adj[i].clear();

    height.resize(n + 1, 0);
    fill(height.begin(), height.end(), 0);
    parentNode.resize(n + 1, 0);
    fill(parentNode.begin(), parentNode.end(), 0);
    dp.resize(n + 1, vector<int>(log2(n) + 1, 0));
    freq.resize(n + 1, vector<int>(26, 0));
    fill(freq.begin(), freq.end(), vector<int>(26, 0));
    maxHeight = 1;

    //building-graph
    for (auto edge : B) {
        int u = edge[0], v = edge[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //Assumption: Rooted @ 1
    dfs(A, 1, 0);

    //building sparse table
    buildSparseTable(A);

    //main-logic
    string result;
    for (auto query : C) {
        int u = query[0], v = query[1];
        int minFreq = INT_MAX;
        char minChar = 'a';
        int lca = getLCA(u, v);

        for (int j = 0; j < 26; j++) {
            int currFreq = freq[u][j] + freq[v][j] - 2 * freq[lca][j] + ((A[lca - 1] - 'a') == j);
            if (currFreq < minFreq && currFreq != 0) {
                minFreq = currFreq;
                minChar = ('a' + j);
            }
        }

        result += minChar;
    }

    return result;
}

int main() {
    // Solution sol= Solution();
    vector<char> A{'q', 'k', 'q', 'j', 'x', 'j', 'a', 'd'};
    vector<vector<int>> B = {
        {8, 2},
        {6, 3},
        {5, 2},
        {3, 1},
        {4, 2},
        {7, 2},
        {2, 1}};
    vector<vector<int>> C = {
        {1, 3},
        {8, 4},
        {2, 4}};

    cout << solve(A, B, C);
    return 0;
}
