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

int n, q;
vector<int> parent(MAX_N), depth(MAX_N);

void init() {
    for (int i = 0; i <= MAX_N; i++)
        parent[i] = i, depth[i] = 0;
}

int find(int node) {
    while (parent[node] != node)
        node = parent[node];
    return node;
}

bool same(int a, int b) {
    if (find(a) == find(b))
        return true;
    return false;
}

void merge(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA == rootB) return;
    if (depth[rootA] < depth[rootB])
        parent[rootA] = rootB;
    else {
        parent[rootB] = rootA;
        depth[rootA] = max(depth[rootA], depth[rootB] + 1);
    }
}

void solve() {
    init();
    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 0) {
            merge(a, b);
            continue;
        }
        if (same(a, b)) cout << "1\n";
        else cout << "0\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
