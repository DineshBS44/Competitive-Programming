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

int criticalConnections(vector<vector<int>> &graph, int n, int node, int myRank, vector<int> &ranks, vector<vector<int>> &result) {
    if (ranks[node] != -2) {
        return ranks[node];
    }
    int lowestRank = myRank;
    ranks[node] = myRank;
    for (auto neighbor : graph[node]) {
        if (ranks[neighbor] == myRank - 1 || ranks[neighbor] == n) {
            continue;
        }
        int neighborRank = criticalConnections(graph, n, neighbor, myRank + 1, ranks, result);
        lowestRank = min(lowestRank, neighborRank);
        if (neighborRank > myRank) {
            result.push_back({node, neighbor});
        }
    }
    ranks[node] = n;
    return lowestRank;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> gr(n);
    // For directed graphs, convert to undirected graph and use this same algo
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    vector<int> ranks(n, -2);
    vector<vector<int>> result;
    criticalConnections(gr, n, 0, 0, ranks, result);
    for (auto i : result) cout << i[0] + 1 << " " << i[1] + 1 << '\n';
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