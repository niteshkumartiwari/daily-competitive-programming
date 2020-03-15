/*
For an undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3 

Output: [1]
Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5 

Output: [3, 4]
Note:

According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
*/
#include <bits/stdc++.h>
#include <unordered_set>
#define ll long long
using namespace std;

class Solution {
   public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<int> res;
        if (n == 1)
            return {0};
        unordered_map<int, unordered_set<int>> adj;
        for (auto entry : edges) {
            adj[entry[0]].insert(entry[1]);
            adj[entry[1]].insert(entry[0]);
        }

        vector<int> leaves;
        for (auto entry : adj) {
            if (adj[entry.first].size() == 1)
                leaves.push_back(entry.first);
        }

        while (n > 2) {
            n -= leaves.size();
            vector<int> nextleaves;
            for (int i = 0; i < leaves.size(); i++) {
                int nextNode = *(adj[leaves[i]].begin());

                adj[leaves[i]].erase(nextNode);
                adj[nextNode].erase(leaves[i]);

                if (adj[nextNode].size() == 1)
                    nextleaves.push_back(nextNode);
            }

            leaves = nextleaves;
        }

        return leaves;
    }
};

int main() {
    Solution sol = Solution();
    vector<vector<int>> edges{
        {0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}};
    int n = 6;

    vector<int> res = sol.findMinHeightTrees(n, edges);
    for (int val : res)
        cout << val << " ";

    return 0;
}
