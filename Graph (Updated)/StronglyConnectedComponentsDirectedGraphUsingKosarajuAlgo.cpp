//
// Created by dines on 10-06-2022.
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
const int MAX_N = 1e5 + 5;

void dfs(vector<vector<int>> &gr, vector<int> &vis, stack<int> &st, int node) {
    vis[node] = 1;
    for (auto x : gr[node]) {
        if (!vis[x]) {
            dfs(gr, vis, st, x);
        }
    }
    st.push(node);
}

void finalDFS(vector<vector<int>> &gr, vector<int> &vis, int node, vector<int> &scc) {
    vis[node] = 1;
    scc.pb(node);
    for (auto x : gr[node]) {
        if (!vis[x]) finalDFS(gr, vis, x, scc);
    }
}

// Using Kosaraju's algorithm
vector<vector<int>> findStronglyConnectedComponents(vector<vector<int>> &gr) {
    int n = gr.size();
    vector<int> vis(n);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if(!vis[i]) dfs(gr, vis, st, i);
    }
    vector<vector<int>> transposeGraph(n);
    for (int i = 0; i < n; i++) {
        for (auto x : gr[i]) transposeGraph[x].pb(i);
    }
    fill(all(vis), 0);
    vector<vector<int>> result;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if(!vis[node]) {
            vector<int> scc;
            finalDFS(transposeGraph, vis, node, scc);
            result.pb(scc);
        }
    }
    return result;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> gr(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        gr[u].pb(v);
    }
    vector<vector<int>> stronglyConnectedComponents = findStronglyConnectedComponents(gr);
    for (auto &i : stronglyConnectedComponents) {
        for (auto &j : i) cout << j + 1 << " ";
        cout << '\n';
    }
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