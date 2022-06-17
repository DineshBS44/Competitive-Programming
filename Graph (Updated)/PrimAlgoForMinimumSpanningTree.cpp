//
// Created by dines on 09-06-2022.
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

vector<int> primAlgo(vector<vector<pair<int, int>>> &gr) {
    int n = gr.size();
    vector<int> key(n, INT_MAX), parent(n, -1), mst(n, false);
    key[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    for (int i = 0; i < n - 1; i++) {
        int node = pq.top().second;
        pq.pop();
        mst[node] = true;
        for (auto x : gr[node]) {
            if (mst[x.first] == false && x.second < key[x.first]) {
                key[x.first] = x.second;
                pq.push({x.second, x.first});
                parent[x.first] = node;
            }
        }
    }
    return parent;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> gr(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v;
        u--, v--;
        gr[u].pb({v, w});
        gr[v].pb({u, w});
    }
    vector<int> parent = primAlgo(gr);
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << '\n';
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