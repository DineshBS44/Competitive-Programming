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
const int MAX = (1 << 20) + 1;
int have[MAX];
void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for (int i = 1; i <= k; i++) {
        string p;
        cin >> p;
        int mask = 0;
        for (auto y:p) {
            mask |= (1 << (y - 'a'));
        }
        have[mask] = i;
    }
    for (int mask = MAX - 1; mask > 0; mask--) {
        if (have[mask]) {
            for (int i = 0; i < 20; i++) {
                if (mask & (1 << i))
                    have[mask ^ (1 << i)] = have[mask];
            }
        }
    }
    auto print_ntimes = [](int num, int rep) {
        for (int i = 0; i < rep; i++)
            cout << num << " ";
    };
    int l = 0, cur_mask = 0;
    for (int i = 0; i < s.size(); i++) {
        int cur_bit = (1 << (s[i] - 'a'));
        if (!have[cur_mask | cur_bit]) {
            print_ntimes(have[cur_mask], i - l);
            l = i;
            cur_mask = cur_bit;
        } else
            cur_mask |= cur_bit;
    }
    print_ntimes(have[cur_mask], n - l);
    cout << "\n";
    memset(have, 0, sizeof(have));
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
