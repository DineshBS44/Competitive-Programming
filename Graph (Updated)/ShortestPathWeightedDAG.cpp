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

vector<int> topoSortBFS(vector<vector<pair<int, int>>> &gr) {
    int n = gr.size();
    vector<int> inDegree(n), topoOrder;
    for (int i = 0; i < n; i++) {
        for (auto x : gr[i]) inDegree[x.first]++;
    }
    queue<int> q;
    for (int i = 0; i < gr.size(); i++) {
        if (inDegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int node = q.front();
        topoOrder.pb(node);
        q.pop();
        for (auto x : gr[node]) {
            inDegree[x.first]--;
            if (!inDegree[x.first]) q.push(x.first);
        }
    }
    return topoOrder;
}

void solve() {
    int n, m, src;
    cin >> n >> m >> src;
    src--; // 0-based indexing
    vector<vector<pair<int, int>>> gr(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v;
        u--, v--;
        gr[u].pb({v, w});
    }
    vector<int> topoOrder = topoSortBFS(gr);
    vector<int> shortestDist(n, INT_MAX);
    shortestDist[src] = 0;
    for (auto i : topoOrder) {
        if (shortestDist[i] != INT_MAX) {
            for (auto x : gr[i]) {
                shortestDist[x.first] = min(shortestDist[x.first], shortestDist[i] + x.second);
            }
        }
    }
    for (auto i : shortestDist) cout << i << " ";
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