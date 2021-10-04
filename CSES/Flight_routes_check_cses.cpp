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

int n, m;
vector<bool> vis(MAX_N);

void dfs(vector<int> graph[], int node) {
    if (vis[node]) return;
    vis[node] = 1;
    for (auto i:graph[node])
        dfs(graph, i);
}

void solve() {
    vector<int> gr[MAX_N], rgr[MAX_N];
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        gr[a].pb(b);
        rgr[b].pb(a);
    }
    dfs(gr, 0);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cout << "NO\n";
            cout << "1 " << i + 1 << "\n";
            return;
        }
    }
    fill(all(vis), 0);
    dfs(rgr, 0);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cout << "NO\n";
            cout << i + 1 << " 1" << "\n";
            return;
        }
    }
    cout << "YES\n";
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
/*#ifndef ONLINE_JUDGE
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);
#endif*/
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}