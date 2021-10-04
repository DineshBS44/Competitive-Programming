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
vector<int> parents[MAX_N];
vector<int> maxDist(MAX_N);
vector<int> pre(MAX_N);

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
        parents[b].pb(a);
    }
    dfs(0);
    reverse(all(topologicalOrder));
    if (!vis[n - 1]) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    set<int> s;
    int flag = 0;
    for (int i = 0; i < (int) topologicalOrder.size(); i++) {
        if (topologicalOrder[i] == 0) {
            flag = 1;
        }
        if (flag)
            maxDist[i] = 1;
        else
            maxDist[i] = -INT_MAX;
        if (topologicalOrder[i] == n - 1)
            flag = 0;
    }
    vector<int> order;
    for (int i = 0; i < (int) topologicalOrder.size(); i++) {
        int len = 1;
        int node = -1;
        for (auto v:parents[topologicalOrder[i]]) {
            if (maxDist[v] + 1 > len) {
                node = v;
                len = maxDist[v] + 1;
            }
        }
        maxDist[topologicalOrder[i]] = len;
        pre[topologicalOrder[i]] = node;
    }
    int node = n - 1;
    while (node != 0) {
        order.pb(node);
        node = pre[node];
    }
    order.pb(0);
    reverse(all(order));
    cout << order.size() << "\n";
    for (auto i:order)
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