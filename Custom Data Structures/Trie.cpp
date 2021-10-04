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

typedef struct Tree {
    Tree *child[26];
    int cnt = 0;
} trie;

int n, k, ans = 0;
vector<string> s(MAX_N);
trie *root;

void insert(string se) {
    trie *cur = root;
    for (int i = 0; i < (int) se.size(); i++) {
        if (!(cur->child[se[i] - 'A'])) {
            cur->child[se[i] - 'A'] = new trie();
        }
        cur = cur->child[se[i] - 'A'];
    }
    cur->cnt += 1;
}

void dfs(Tree *node, int h) {
    int val = node->cnt;
    for (int i = 0; i < 26; i++) {
        if (node->child[i]) {
            dfs(node->child[i], h + 1);
            val += node->child[i]->cnt;
        }
    }
    while (val >= k) {
        val -= k;
        ans += h;
    }
    node->cnt = val;
}

void solve() {
    cin >> n >> k;
    root = new trie();
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        insert(s[i]);
    }
    ans = 0;
    dfs(root, 0);
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    int tc = 0;
    while (t--) {
        ++tc;
        cout << "Case #" << tc << ": ";
        solve();
    }
    return 0;
}
