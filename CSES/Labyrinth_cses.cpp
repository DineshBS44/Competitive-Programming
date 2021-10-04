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

vector<vector<char>> gr(MAX_N, vector<char>(MAX_N, '-'));
vector<vector<int>> vis(MAX_N, vector<int>(MAX_N, 0));
vector<vector<int>> dist(MAX_N, vector<int>(MAX_N, 0));
vector<vector<pair<int, int>>> pre(MAX_N, vector<pair<int, int>>(MAX_N, {-1, -1}));
int n, m;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};


bool poss(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && gr[x][y] != '#');
}

void bfs(int node, int node2) {
    queue<pair<int, int>> q;
    q.push({node, node2});
    vis[node][node2] = 1;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = cur.F + dr[i];
            int y = cur.S + dc[i];
            if (poss(x, y) && !vis[x][y]) {
                vis[x][y] = 1;
                dist[x][y] = dist[cur.F][cur.S] + 1;
                q.push({x, y});
                pre[x][y] = {cur.F, cur.S};
            }
        }
    }
}

char findChar(pair<int, int> p) {
    int x = p.F, y = p.S;
    if (x == 1 && y == 0)
        return 'D';
    if (x == -1 && y == 0)
        return 'U';
    if (x == 0 && y == 1)
        return 'R';
    return 'L';
}

void solve() {
    cin >> n >> m;
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> gr[i][j];
            if (gr[i][j] == 'A') {
                x1 = i, y1 = j;
            } else if (gr[i][j] == 'B') {
                x2 = i;
                y2 = j;
            }
        }
    }
    bfs(x1, y1);
    if (!vis[x2][y2]) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << dist[x2][y2] << "\n";
    string s = "";
    int x = x2, y = y2;
    pair<int, int> p = pre[x][y];
    pair<int, int> val = {x - p.F, y - p.S};
    char c = findChar(val);
    x = p.F;
    y = p.S;
    while (x != -1) {
        s += c;
        p = pre[x][y];
        val = {x - p.F, y - p.S};
        c = findChar(val);
        x = p.F, y = p.S;
    }
    reverse(all(s));
    cout << s << "\n";
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