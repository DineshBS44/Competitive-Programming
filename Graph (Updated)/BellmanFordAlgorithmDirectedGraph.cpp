//
// Created by dines on 10-06-2022.
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
const int MAX_N = 1e5 + 5;

// Bellman Ford Algorithm
// Helps in finding Negative cost cycles, but only gives answer when there are no negative cycles.
// It is impossible to have an answer with a Negative cost cycle.
// For negative cost cycles, Dijkstra's algo will fail and will not even detect them, instead just gives a wrong answer


struct Node {
    int u, v, w;
    Node(int _u, int _v, int _w) {
        u = _u, v = _v, w = _w;
    }
};

void solve() {
    int n, m, src;
    cin >> n >> m >> src;
    src--;
    vector<Node> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.pb({u, v, w});
    }
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for(int i = 0; i < n - 1; i++) {
        for(auto &edge : edges) {
            dist[edge.v] = min(dist[edge.v], dist[edge.u] + edge.w);
        }
    }
    bool hasNegativeCycle = true;
    for(auto edge : edges) {
        if(dist[edge.u] + edge.w < dist[edge.v]) {
            hasNegativeCycle = false;
            dist[edge.v] = dist[edge.u] + edge.w;
        }
    }
    if(hasNegativeCycle) {
        cout << "Negative Cycle Detected\n";
    } else {
        for(int i = 0; i < n; i++) {
            cout << i + 1 << " " << dist[i] << '\n';
        }
    }
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