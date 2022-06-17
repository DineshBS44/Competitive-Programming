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

bool hasCycleDFS(vector<vector<int>> &gr, vector<int> &vis, int node, int par) {
    vis[node] = 1;
    for (auto x: gr[node]) {
        if (!vis[x]) {
            if (hasCycleDFS(gr, vis, x, node)) return true;
        } else if (x != par) return true;
    }
    return false;
}

bool hasCycleBFS(vector<vector<int>> &gr, vector<int> &vis, int node) {
    queue<pair<int, int>> q;
    q.push({node, -1});
    while(!q.empty()) {
        int curNode = q.front().first;
        int parent = q.front().second;
        vis[curNode] = 1;
        q.pop();
        for(auto x : gr[curNode]) {
            if(!vis[x]) {
                q.push({x, curNode});
            } else if(x != parent) return true;
        }
    }
    return false;
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
    vector<int> vis(n);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (hasCycleDFS(gr, vis, i, -1)) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
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
