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
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        ranks[i] = 0;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        union_by_rank(a, b);
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
