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
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int l = 1, r = d;
    int ans = 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        bool poss = true;
        vector<int> b = a;
        if (b[0] < mid) {
            if (mid % b[0] == 0) {
                b[0] *= (mid / b[0]);
            } else
                b[0] *= (mid / b[0] + 1);
        }
        for (int i = 1; i < n; i++) {
            if (b[i] < b[i - 1]) {
                if (b[i - 1] % b[i] == 0) {
                    b[i] *= (b[i - 1] / b[i]);
                } else
                    b[i] *= (b[i - 1] / b[i] + 1);
            }
            if (b[i] > d) {
                poss = false;
                break;
            }
        }
        if (poss) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
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
