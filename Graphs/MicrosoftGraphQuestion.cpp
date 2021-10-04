#include<bits/stdc++.h>

using namespace std;

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
vector<vector<int>> gr(MAX_N);
vector<int> vis(MAX_N);
vector<int> numNodes(MAX_N);
vector<int> cost(MAX_N);

int dfs(int node) {
    vis[node] = 1;
    for (auto i:gr[node]) {
        if (vis[i])
            continue;
        int nodes = dfs(i);
        numNodes[node] += nodes;
        int costNode = cost[i];
        int carsNeeded = ceil(((double) nodes) / ((double) 5));
        int totCost = costNode + carsNeeded;
        cost[node] += totCost;
    }
    return numNodes[node] + 1;
}

int solution(vector<int> &A, vector<int> &B) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        gr[A[i]].push_back(B[i]);
        gr[B[i]].push_back(A[i]);
    }
    dfs(0);
    int ans = cost[0];
    for (int i = 0; i < n + 1; i++) {
        gr[i].clear();
        vis[i] = 0;
        numNodes[i] = 0;
        cost[i] = 0;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
        cin >> b[i];

    int ans = solution(a, b);
    cout << ans << "\n";
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
