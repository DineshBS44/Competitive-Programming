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

int l;
int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(vector<vector<pair<int, int>>> &adj, int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (auto u : adj[v]) {
        if (u.F != p)
            dfs(adj, u.F, v);
    }
    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(vector<vector<pair<int, int>>> &adj, int root, int n) {
    tin.resize(n + 1);
    tout.resize(n + 1);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n + 1, vector<int>(l + 1));
    dfs(adj, root, root);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= l; j++)
            cout << up[i][j] << " ";
        cout << "\n";
    }
}

void setCost(vector<int> &cost, vector<int> &vis, vector<vector<pair<int, int>>> &adj,
             int n, int r) {
    for (auto i : adj[r]) {
        if (!vis[i.F]) {
            cost[i.F] = i.S + cost[r];
            vis[i.F] = 1;
            setCost(cost, vis, adj, n, i.F);
        }
    }
}

void solve() {
    int n, q, r;
    cin >> n >> q >> r; //r is the root node
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    vis[r] = 1;
    vector<int> cost(n + 1, 0);
    setCost(cost, vis, adj, n, r);
    preprocess(adj, r, n);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        int ans = cost[u] + cost[v] - 2 * cost[lca(u, v)]; // minimum path sum from node u to v
        cout << ans << "\n";
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

// Test case
/*
Input:
1
9 3 1
1 2 2
1 3 2
2 4 3
2 5 3
3 6 3
3 7 3
5 8 4
5 9 4
8 7
4 6
1 3

Output:
14
10
2  */