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

bool isBipartiteBFS(vector<vector<int>> &gr, vector<int> &color, int node) {
    queue<int> q;
    q.push(node);
    color[node] = 0;
    while (!q.empty()) {
        int curNode = q.front();
        q.pop();
        for (auto x : gr[curNode]) {
            if (color[x] == -1) {
                color[x] = 1 - color[curNode];
                q.push(x);
            } else if (color[x] == color[curNode]) return false;
        }
    }
    return true;
}

bool isBipartiteDFS(vector<vector<int>> &gr, vector<int> &color, int node) {
    if (color[node] == -1) color[node] = 0;
    for (auto x : gr[node]) {
        if (color[x] == -1) {
            color[x] = 1 - color[node];
            if (!isBipartiteDFS(gr, color, node)) return false;
        } else if (color[x] == color[node]) return false;
    }
    return true;
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
        gr[v].pb(u);
    }
    vector<int> color(n, -1);
    for (int i = 0; i < n; i++) {
        if (!color[i]) {
            if (!isBipartiteBFS(gr, color, i)) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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

