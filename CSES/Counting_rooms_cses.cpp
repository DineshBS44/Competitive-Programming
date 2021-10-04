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
const int MAX_N = 1e3 + 5;

vector<vector<char>> gr(MAX_N, vector<char>(MAX_N, 0));
vector<vector<char>> vis(MAX_N, vector<char>(MAX_N, 0));
int n, m;

void dfs(int x, int y) {
    if (x < 0 || y < 0 || x > n - 1 || y > m - 1) return;
    if (vis[x][y]) return;
    if (gr[x][y] != '.') return;
    vis[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> gr[i][j];
    }
    int rooms = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (gr[i][j] == '.' && !vis[i][j]) {
                dfs(i, j);
                rooms++;
            }
        }
    }
    cout << rooms << "\n";
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