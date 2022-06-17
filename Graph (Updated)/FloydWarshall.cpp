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
const int MAX_N = 5e2 + 5;

int n, m, q;
vector<vector<int>> gr(MAX_N, vector<int>(MAX_N, INF));
vector<vector<int>> weights(MAX_N, vector<int>(MAX_N));

void computeShortest() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                weights[i][j] = 0;
            else
                weights[i][j] = gr[i][j];
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                weights[i][j] = min(weights[i][j], weights[i][k] + weights[k][j]);
            }
        }
    }
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        gr[a][b] = min(gr[a][b], c);
        gr[b][a] = min(gr[b][a], c);
    }
    computeShortest();
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << (weights[a][b] == INF ? -1 : weights[a][b]) << "\n";
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
