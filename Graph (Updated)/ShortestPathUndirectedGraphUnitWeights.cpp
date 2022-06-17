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

vector<int> calculateShortestDistanceBFS(vector<vector<int>> &gr, int src) {
    int n = gr.size();
    queue<int> q;
    vector<int> dist(n, INT_MAX);
    q.push(src);
    dist[src] = 0;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(auto x : gr[node]) {
            if(dist[node] + 1 < dist[x]) {
                dist[x] = dist[node] + 1;
                q.push(x);
            }
        }
    }
    return dist;
}

void solve() {
    int n, m, src;
    cin >> n >> m >> src;
    src--; // 0-based indexing
    vector<vector<int>> gr(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    vector<int> shortestDist = calculateShortestDistanceBFS(gr, src);
    for(auto i : shortestDist) cout << i << " ";
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