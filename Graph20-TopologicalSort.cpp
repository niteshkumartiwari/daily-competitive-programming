/*
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 6;

vector<int> adj[6];

/*
        5---->2-------->3
        |               |
        |               |
        |               |
        \/              \/
        0<------4------->1
*/

void vanillaTopologicalSortUtil(int u, vector<bool> &visited, stack<int> &st) {
    visited[u] = true;

    for (auto v : adj[u]) {
        if (!visited[v])
            vanillaTopologicalSortUtil(v, visited, st);
    }

    st.push(u);
}

void vanillaTopologicalSort() {  //O(E+V)
    stack<int> st;
    vector<bool> visited(N, false);

    for (int i = 0; i < N; i++)
        if (!visited[i])
            vanillaTopologicalSortUtil(i, visited, st);

    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
}

void kahnTopologicalSort() {  //O(E+V)
    vector<int> in_degree(N, 0);

    for (int i = 0; i < N; i++) {
        for (auto v : adj[i])
            in_degree[v]++;
    }

    queue<int> q;

    for (int i = 0; i < N; i++)
        if (in_degree[i] == 0)
            q.push(i);

    int cnt = 0;
    vector<int> top_order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        for (auto v : adj[u])
            if (--in_degree[v] == 0) q.push(v);

        cnt++;
    }

    if (cnt != N)
        cout << "There exists a cycle in the graph" << endl;

    for (int i = 0; i < top_order.size(); i++)
        cout << top_order[i] << " ";

    cout << endl;
}

int main() {
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    //vanillaTopologicalSort();
    kahnTopologicalSort();

    return 0;
}
