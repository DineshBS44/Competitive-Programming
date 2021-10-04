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
const int MAX_N = 5e5 + 5;

int ans = 0;
vector<vector<int>> va(1e5 + 5);
vector<int> a(MAX_N);
vector<int> m2(MAX_N);
vector<int> c(MAX_N);
vector<int> b(MAX_N);

int merge(vector<int> &arr, vector<int> &temp, int left, int mid, int right) {
    int inv_count = 0;
    int i = left;
    int j = mid;
    int k = left;
    vector<int> pref(mid-left);
    pref[0] = m2[arr[left]];
    for (int l = left + 1; l < mid; l++) {
        pref[l-left] = pref[l - 1 - left] + m2[arr[l]];
    }
    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else {
            int val = pref[mid - 1 - left];
            int len = mid - i;
            if (i > left)
                val -= pref[i - 1 - left];
            ans += val - len * m2[arr[j]];
            temp[k++] = arr[j++];

            inv_count = inv_count + (mid - i);
        }
    }
    while (i <= mid - 1)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

int _mergeSort(vector<int> &arr, vector<int> &temp, int left, int right) {
    int mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;
        inv_count = _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid + 1, right);
        inv_count += merge(arr, temp, left, mid + 1, right);
    }

    return inv_count;
}

int findCost(vector<int> &arr, int n) {
    vector<int> temp(n);
    return _mergeSort(arr, temp, 0, n - 1);
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        va[b[i]].pb(i);
    }
    for (int i = 0; i < n; i++) {
        int ind = va[a[i]].back();
        va[a[i]].pop_back();
        c[i] = ind;
        m2[c[i]] = a[i];
    }
    ans = 0;
    int val1 = findCost(c, n);
    cout << ans << "\n";
    for (int i = 0; i < n; i++) {
        va[b[i]].clear();
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
