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
const int MAX_N = 1e5 + 5;

vector<int> parent(MAX_N), ranks(MAX_N);

struct Node {
    int u, v, w;

    Node(int firstNode, int secondNode, int weight) {
        u = firstNode, v = secondNode, w = weight;
    }
};

bool comp(Node a, Node b) {
    return a.w <= b.w;
}

int findPar(int node) {
    if (parent[node] == node) {
        return node;
    }
    return parent[node] = findPar(parent[node]);
}

void union_by_rank(int a, int b) {
    int parA = findPar(a), parB = findPar(b);
    if (ranks[parA] < ranks[parB]) {
        parent[parA] = parB;
    } else if (ranks[parA] > ranks[parB]) {
        parent[parB] = parA;
    } else {
        parent[parB] = parA;
        ranks[parA]++;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        ranks[i] = 0;
    }
    vector<Node> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.pb(Node(u, v, w));
    }
    sort(all(edges), comp);
    int cost = 0;
    int numEdges = n - 1, ind = 0;
    vector<pair<int, int>> mst;
    while (numEdges) {
        int parentU = findPar(edges[ind].u);
        int parentV = findPar(edges[ind].v);
        if (parentU == parentV) {
            ind++;
            continue;
        }
        cost += edges[ind].w;
        union_by_rank(edges[ind].u, edges[ind].v);
        mst.pb({edges[ind].u, edges[ind].v});
        ind++, numEdges--;
    }
    cout << "cost: " << cost << '\n';
    for (auto i : mst) cout << i.first << " " << i.second << '\n';
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