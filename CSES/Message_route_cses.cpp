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

vector<int> adj[MAX_N];
vector<int> vis(MAX_N);
vector<int> dist(MAX_N);
vector<int> pre(MAX_N);
int n, m;

void bfs(int node) {
    queue<int> q;
    q.push(node);
    pre[node] = -1;
    vis[node] = 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto x:adj[cur]) {
            if (!vis[x]) {
                vis[x] = 1;
                dist[x] = dist[cur] + 1;
                pre[x] = cur;
                q.push(x);
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    bfs(0);
    if (!vis[n - 1]) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << dist[n - 1] + 1 << "\n";
    int node = n - 1;
    vector<int> res;
    while (node != -1) {
        res.pb(node);
        node = pre[node];
    }
    for (int i = res.size() - 1; i >= 0; i--)
        cout << res[i] + 1 << " ";
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