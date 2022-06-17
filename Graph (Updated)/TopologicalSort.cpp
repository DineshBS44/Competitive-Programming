//
// Created by dinesh on 09-06-2022.
//

#include<bits/stdc++.h>
using namespace std;

#define int long long int
#define ld long double
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define pll pair<int,int>
#define MOD 1000000007
#define M2 998244353
#define INF 2e18
#define EPS 1e-9
#define minheap priority_queue<int, vector<int>, greater<int>>
const ld PI = 3.14159265358979323846;
const int MAX_N = 1e6 + 5;

// Topological sort is only possible for DAG
// If there is an edge: u->v, then 'u' must occur before 'v' in the ordering

void topoSortDFS(vector<vector<int>> &gr, vector<int> &vis, vector<int> &topoOrder, int node) {
    vis[node] = 1;
    for (auto x : gr[node]) {
        if (!vis[x]) {
            topoSortDFS(gr, vis, topoOrder, x);
        }
    }
    topoOrder.pb(node);
}

void topoSortBFS(vector<vector<int>> &gr, vector<int> &topoOrder, vector<int> &inDegree) {
    queue<int> q;
    for (int i = 0; i < gr.size(); i++) {
        if (inDegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int node = q.front();
        topoOrder.pb(node);
        q.pop();
        for (auto x : gr[node]) {
            inDegree[x]--;
            if (!inDegree[x]) q.push(x);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> gr(n);
    vector<int> inDegree(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        gr[u].pb(v);
        inDegree[v]++;
    }
    vector<int> vis(n), topoOrder;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            topoSortDFS(gr, vis, topoOrder, i);
        }
    }
    reverse(all(topoOrder)); // only for DFS

    // For BFS using Kahn's Algorithm
    // topoSortBFS(gr, topoOrder, inDegree);

    for (auto i : topoOrder) cout << i + 1 << " ";
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}