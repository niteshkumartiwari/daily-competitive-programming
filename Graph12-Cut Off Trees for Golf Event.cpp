/*
You are asked to cut off trees in a forest for a golf event. The forest is represented as a non-negative 2D map, in this map:

0 represents the obstacle can't be reached.
1 represents the ground can be walked through.
The place with number bigger than 1 represents a tree can be walked through, and this positive number represents the tree's height.
 

You are asked to cut off all the trees in this forest in the order of tree's height - always cut off the tree with lowest height first. And after cutting, the original place has the tree will become a grass (value 1).

You will start from the point (0, 0) and you should output the minimum steps you need to walk to cut off all the trees. If you can't cut off all the trees, output -1 in that situation.

You are guaranteed that no two trees have the same height and there is at least one tree needs to be cut off.

Example 1:

Input: 
[
 [1,2,3],
 [0,0,4],
 [7,6,5]
]
Output: 6
 

Example 2:

Input: 
[
 [1,2,3],
 [0,0,0],
 [7,6,5]
]
Output: -1
 

Example 3:

Input: 
[
 [2,3,4],
 [0,0,5],
 [8,7,6]
]
Output: 6
Explanation: You started from the point (0,0) and you can cut off the tree in (0,0) directly without walking.
 

Hint: size of the given matrix will not exceed 50x50.
*/

//Logic is correct but code is not working
#include<bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> ti;
typedef pair<int,int> pi;

class Solution {     
    int BFS(int ux,int uy,int tx,int ty,int n,int m,vector<vector<int>> &forest){
        if (ux == tx && uy == ty) return 0;
        queue<pi> q;
        q.push({ux,uy});
        int res=0;
        int dir[][2]={{1,0},{0,1},{-1,0},{0,-1}};
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        visited[ux][uy]=true;   

        while(!q.empty()){
            int size=q.size();
            res++;
            for(int j=0;j<size;j++){
                auto u=q.front();q.pop();
                for(int k=0;k<4;k++){
                    int vx=u.first+dir[k][0],vy=u.second+dir[k][1];

                    if(vx<0 || vx>=n || vy<0 ||vy>=m || visited[vx][vy] || forest[vx][vy]==0) continue;
                    if(vx==tx && vy==ty) return res;

                    q.push({vx,vy});
                    visited[vx][vy]=true;
                }
            }
        }

        return -1;
    };
public:
    int cutOffTree(vector<vector<int>>& forest) {
        int n=forest.size(),m=forest[0].size();
        vector<vector<int> > flatten;
        
        if(forest[0][0]==0) return -1;
        
        forest[0][0]=1;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(forest[i][j] >1)
                    flatten.push_back({forest[i][j],i,j});
            }
        }

        sort(flatten.begin(),flatten.end());   

        int steps=0;
        int ux=0,uy=0;
        for(int i=0;i<flatten.size();i++){
            int tx=flatten[i][1],ty=flatten[i][2];
            int reached=BFS(ux,uy,tx,ty,n,m,forest);
            if(reached==-1) return -1;
            steps+=reached;
            ux=tx;uy=ty;
        }

        return steps;
    }
};//O(M^2*N^2)

int main(){
    vector<vector<int>> forest{
        {54581641,64080174,24346381,69107959},
        {86374198,61363882,68783324,79706116},
        {668150,92178815,89819108,  94701471},
        {83920491,22724204,46281641,47531096},
        {89078499,18904913,25462145,60813308}
    };

    Solution sol= Solution();

    cout<<sol.cutOffTree(forest);

    return 0;
}