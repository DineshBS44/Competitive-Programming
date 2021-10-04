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

vector<int> gr[MAX_N];
vector<bool> vis(MAX_N);
vector<int> team(MAX_N);
int n, m;
bool ok = true;
int team_number = 1;

void graph_coloring(int node) {
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            int cur_node = q.front();
            q.pop();
            vis[cur_node] = 1;
            team[cur_node] = team_number;
            for (auto j:gr[cur_node]) {
                if (!vis[j]) {
                    q.push(j);
                } else {
                    if (team_number == team[j])
                        ok = false;
                }
            }
        }
        team_number = 3 - team_number;
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        gr[a].pb(b);
        gr[b].pb(a);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i])
            graph_coloring(i);
    }
    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (int i = 0; i < n; i++)
        cout << team[i] << " ";
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
/*#ifndef ONLINE_JUDGE
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
#endif*/
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}