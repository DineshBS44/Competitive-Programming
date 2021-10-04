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

vector<vector<int>> gr(MAX_N);
vector<int> vis(MAX_N);
int n;

bool check_bipartite(int s) {
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (auto y:gr[x]) {
            if (!vis[y]) {
                Q.push(y);
                vis[y] = 3 - vis[x];
            } else if (vis[y] == vis[x])
                return false;
        }
    }
    return true;
}

void solve() {
    cin >> n;
    vector<pair<pair<int, int>, int>> v;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        v.pb({{a, b}, c});
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i].S == v[j].S) {
                if (!(v[j].F.S < v[i].F.F || v[i].F.S < v[j].F.F)) {
                    gr[i].pb(j);
                    gr[j].pb(i);
                }
            }
        }
    }
    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            ans &= check_bipartite(i);
        }
    }
    if (ans)
        cout << "YES\n";
    else
        cout << "NO\n";
    for (int i = 0; i < n; i++) {
        gr[i].clear();
        vis[i] = 0;
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
