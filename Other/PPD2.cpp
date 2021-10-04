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
    int n;
    cin >> n;
    string s = to_string(n);
    int len = s.size();
    int ans = 0;
    ans += (len - 1) * 9;
    string ne = "";
    for (int i = 0; i < len; i++) {
        ne += s[0];
    }
    if (ne <= s) {
        ans += ((int) (s[0] - '0'));
    } else {
        ans += ((int) (s[0] - '0')) - 1;
    }
    cout << ans << "\n";
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
