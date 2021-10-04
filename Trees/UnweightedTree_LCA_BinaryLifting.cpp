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
const int MAX_N = 3e5 + 5;

int n, l;
vector<vector<int>> adj;
int timer;
vector<int> tin, tout;
vector<vector<int>> up;
vector<int> depth(MAX_N);

void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (int u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
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

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

int findNode(int a, int len) {
    if (len == 0)
        return a;
    int mov = log2(len);
    int node = up[a][mov];
    return findNode(node, len - (int) pow(2, mov));
}

void solve() {
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    preprocess(0);
    int q;
    cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        int node = lca(a, b);
        if (node == a) {
            int len = depth[b] - depth[a];
            if (len <= c) {
                cout << b + 1 << "\n";
                continue;
            }
            len = len - c;
            cout << findNode(b, len) + 1 << "\n";
        } else if (node == b) {
            int len = depth[a] - depth[b];
            if (len <= c) {
                cout << b + 1 << "\n";
                continue;
            }
            cout << findNode(a, c) + 1 << "\n";
        } else {
            int len1 = depth[a] - depth[node];
            int len2 = depth[b] - depth[node];
            if (c >= len1 + len2) {
                cout << b + 1 << "\n";
                continue;
            }
            if (c <= len1) {
                cout << findNode(a, c) + 1 << "\n";
            } else {
                len2 -= (c - len1);
                cout << findNode(b, len2) + 1 << "\n";
            }
        }
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

// Link: https://codeforces.com/gym/102694/problem/C
