/*
Time Complexity: O(ElogE) or O(ElogV). Sorting of edges takes O(ELogE) time. After sorting, we iterate through all edges and apply 
find-union algorithm. The find and union operations can take atmost O(LogV) time. So overall complexity is O(ELogE + ELogV) time. 
The value of E can be atmost O(V2), so O(LogV) are O(LogE) same. Therefore, overall time complexity is O(ElogE) or O(ElogV)
*/

#include<bits/stdc++.h>
using namespace std;

vector<int> parent;
vector<int> _rank;

int find(int x){
    if(parent[x]!=x){
        parent[x]=find(parent[x]);
    }
    return parent[x];
}

void _union(int x,int y){
    int px=find(x);
    int py=find(y);

    if(_rank[px] > _rank[py])
        parent[py]=px;
    else if(_rank[py] > _rank[px])
        parent[px]=py;
    else{
        parent[py]=px;
        _rank[px]++;
    }  
}

bool customSort(vector<int> a,vector<int> b){
    return a[2] < b[2];
}

int solve(int V, vector<vector<int> > &edges) {
    parent.clear();
    _rank.clear();

    parent.resize(V+1);
    iota(parent.begin(),parent.end(),0);
    _rank.resize(V+1,0);

    sort(edges.begin(),edges.end(),customSort);//increasing-order edges

    int e=0,i=0;

    int cost=0;
    while(e<V && i<edges.size()){
        auto u= edges[i++];

        int x= find(u[0]);
        int y= find(u[1]);

        if(x!=y){
            _union(x,y);
            cost+=u[2];
        }
    }

    return cost;
}


int main(){
    int V=4;
    vector<vector<int>> A{
        {1,2,1},
        {2,3,2},
        {3,4,4},
        {1,4,3}
    };

    cout<<solve(V,A);

    return 0;
}