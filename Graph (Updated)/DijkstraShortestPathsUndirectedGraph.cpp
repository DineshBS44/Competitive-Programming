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

// Dijkstra can be used for both Directed and Undirected graphs
// In Undirected graphs, it is possible to have an answer only when none of the edge weights are negative
// In Directed graph with Negative cost cycles, Dijkstra will just return a wrong answer because it cannot detect these negative cost cycles. Here, Bellman Ford can be used to detect them.
// If there are no cycles in a Directed Graph, i.e the graph is a DAG (Directed Acyclic Graph), then a simpler algorithm using Topological Sort with Time complexity O(N + E) can be used.

vector<int> findShortestPaths(vector<vector<pair<int, int>>> &gr, int src) {
    int n = gr.size();
    vector<int> shortestDist(n, INT_MAX);
    shortestDist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        for (auto x : gr[node]) {
            if (dist + x.second < shortestDist[x.first]) {
                shortestDist[x.first] = dist + x.second;
                pq.push({shortestDist[x.first], x.first});
            }
        }
    }
    return shortestDist;
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
        gr[v].pb({u, w});
    }
    vector<int> shortestDist = findShortestPaths(gr, src);
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