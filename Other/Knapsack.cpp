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

void solve() {
    int n, k, p;
    cin >> n >> k >> p;
    vector<vector<int>> a(n, vector<int>(k + 1, 0));
    vector<vector<int>> sum(n, vector<int>(k + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            cin >> a[i][j];
            sum[i][j] = sum[i][j - 1] + a[i][j];
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(p + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= p; j++) {
            dp[i][j] = 0;
            for (int x = 0; x <= min(j, k); x++) {
                dp[i][j] = max(dp[i][j], sum[i - 1][x] + dp[i - 1][j - x]);
            }
        }
    }
    cout << dp[n][p] << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}
