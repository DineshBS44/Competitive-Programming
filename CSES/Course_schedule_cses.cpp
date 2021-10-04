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

int n, m;
vector<int> vis(MAX_N);
vector<int> gr[MAX_N];
vector<int> topologicalOrder;

bool dfs(int node) {
    vis[node] = 1;
    bool ret = true;
    for (auto v:gr[node]) {
        if (vis[v] == 1) {
            ret = false;
            continue;
        }
        if (vis[v] == 2)
            continue;
        ret &= dfs(v);
    }
    vis[node] = 2;
    topologicalOrder.pb(node);
    return ret;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        gr[a].pb(b);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (!dfs(i)) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }
    reverse(all(topologicalOrder));
    for (auto i:topologicalOrder)
        cout << i + 1 << " ";
    cout << "\n";
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