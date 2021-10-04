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
#define pi pair<int,int>
#define minheap priority_queue<int, vector<int>, greater<int>>
const ld PI = 3.14159265358979323846;
const int MAX_N = 3e5 + 5;

int l;
int timer;
vector<int> tin, tout;
vector<vector<int>> up;
vector<vector<int>> minWeight;
vector<vector<pair<int, int>>> adj;
vector<int> depth;

void dfs(pi v, int p) {
    tin[v.F] = ++timer;
    up[v.F][0] = p;
    minWeight[v.F][0] = v.S;
    for (int i = 1; i <= l; ++i) {
        up[v.F][i] = up[up[v.F][i - 1]][i - 1];
        minWeight[v.F][i] = min(minWeight[v.F][i - 1], minWeight[up[v.F][i - 1]][i - 1]);
    }
    for (auto u : adj[v.F]) {
        if (u.F != p) {
            depth[u.F] = depth[v.F] + 1;
            dfs(u, v.F);
        }
    }
    tout[v.F] = ++timer;
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

void preprocess(pi root, int n) {
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    minWeight.assign(n, vector<int>(l + 1));
    dfs(root, root.F);
}

int findMinWeight(int a, int len, int mini) {
    if (len == 0)
        return mini;
    int steps = log2(len);
    mini = min(mini, minWeight[a][steps]);
    return findMinWeight(up[a][steps], len - (int) pow(2, steps), mini);
}

void solve() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
    }
    preprocess({0, 1e14}, n);
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        int node = lca(a, b);
        int len1 = depth[a] - depth[node];
        int len2 = depth[b] - depth[node];
        int dep1 = findMinWeight(a, len1, 1e15);
        int dep2 = findMinWeight(b, len2, 1e15);
        cout << min(dep1, dep2) << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

//Link: https://codeforces.com/gym/102694/problem/D
