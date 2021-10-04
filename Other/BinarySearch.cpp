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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int maxi = 1;
    for (int i = 1; i < n; i++) {
        maxi = max(maxi, a[i] - a[i - 1]);
    }
    int l = 1, r = maxi;
    int ans = r;
    while (l <= r) {
        int mid = (l + r) / 2;
        int cur = k;
        bool poss = true;
        for (int i = 1; i < n; i++) {
            int diff = a[i] - a[i - 1];
            int c = (diff - 1) / mid;
            cur -= c;
            if (cur < 0) {
                poss = false;
                break;
            }
        }
        if (poss) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
