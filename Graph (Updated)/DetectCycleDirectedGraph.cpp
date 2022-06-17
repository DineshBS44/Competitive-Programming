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

bool hasCycleDFS(vector<vector<int>> &gr, vector<int> &vis, int node) {
    vis[node] = 2;
    for (auto x: gr[node]) {
        if (!vis[x]) {
            if (hasCycleDFS(gr, vis, x)) return true;
        } else if (vis[x] == 2) return true;
    }
    vis[node] = 1;
    return false;
}

bool hasCycleBFS(vector<vector<int>> &gr) {
    int n = gr.size();
    vector<int> inDegree(n);
    for (int i = 0; i < n; i++) {
        for (auto x : gr[i]) inDegree[x]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDegree[i]) q.push(i);
    }
    int cnt = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cnt++;
        for (auto x : gr[node]) {
            inDegree[x]--;
            if (!inDegree[x]) q.push(x);
        }
    }
    if(cnt != n) return true;
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
    }
    vector<int> vis(n);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (hasCycleDFS(gr, vis, i)) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";

    // For BFS using Kahn's algorithm
    // if(hasCycleBFS(gr)) cout << "YES\n";
    // else cout << "NO\n";
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

//    Example:
//    1
//    9 10
//    1 2
//    2 3
//    3 4
//    4 5
//    3 6
//    6 5
//    7 2
//    7 8
//    8 9
//    9 7
//
//    Ans: YES