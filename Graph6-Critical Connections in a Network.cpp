/*
There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network where connections[i] = [a, b] represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some server unable to reach some other server.

Return all critical connections in the network in any order.

*/
#include<bits/stdc++.h>
using namespace std;


vector<vector<int>> adj;
vector<bool> visited;
vector<int> disc;//when node is discovered first
vector<int> low;//min-time reachable node, gives the idea about the back-edge

class Solution {//tarjon algorithm
	void dfs(int u ,int parent,int &time,vector<vector<int>> &res){
		visited[u]=true;
		disc[u]=low[u]=++time;//first time reached
		
		for(auto v: adj[u]){
			if(!visited[v]){
				dfs(v,u,time,res);
				low[u]=min(low[u],low[v]);//update with child's low time
				if(disc[u]<low[v])//min-time to reach child is greater than parent's discovered time (i.e. no-backedge in the subtree rooted at v)
					res.push_back({u,v});
			}
			else if(parent != v)//back-edge
			    low[u]=min(low[u],disc[v]);           
		}
	}
	
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
		adj.clear();
		visited.clear();
		disc.clear();
		low.clear();
        adj.resize(n,vector<int>());
        visited.resize(n,false);
        disc.resize(n,-1);
        low.resize(n,0);
        
        
        for(int i=0;i<connections.size();i++){
        	int u= connections[i][0], v= connections[i][1];
        	adj[u].push_back(v);
        	adj[v].push_back(u);
        }
        
        vector<vector<int>> res;
        vector<bool> visited(n,false);
        int time=0;
        
        for(int i=0;i<n;i++)
            dfs(i,-1,time,res);
        
        return res;
    }
};

int main(){

	return 0;
}
