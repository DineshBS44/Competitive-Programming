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
const ld PI = 3.14159265358979323846;
const int MAX_N = 1e6 + 5;

vector<int> LIS(const vector<int> &elements) {
    // declare the set with a custom comparison function
    // that compares values instead of indices
    auto compare = [&](int x, int y) {
        return elements[x] < elements[y];
    };
    set<int, decltype(compare)> S(compare);

    // process the elements; for each length
    // maintain the index of the best end so far
    vector<int> previous(elements.size(), -1);
    for (int i = 0; i < (int) elements.size(); ++i) {
        auto it = S.insert(i).first;
        if (it != S.begin())
            previous[i] = *prev(it);
        if (*it == i && next(it) != S.end())
            S.erase(next(it));
    }

    // reconstruct the indices that form
    // one possible optimal answer
    vector<int> answer;
    answer.push_back(*S.rbegin());
    while (previous[answer.back()] != -1)
        answer.push_back(previous[answer.back()]);
    reverse(answer.begin(), answer.end());
    return answer;
}

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
//Recursive
int modExp(int a, int b, int m) {
    if (b == 0) return 1;
    int res = modExp(a, b / 2, m);
    res = (res * res) % m;
    if (b & 1) res = (res * a) % m;
    return res;
}
//Iterative(slightly faster)
int binpow(int a, int b, int mod) {
    int ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b = b >> 1;
    }
    return ans;
}

vector<bool> sieve(int n) {
    vector<bool> prime(n + 1);
    for (int i = 0; i <= n; i++)
        prime[i] = 1;
    for (int p = 2; p * p <= n; p++) {
        if (prime[p] == 1) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = 0;
        }
    }
    prime[1] = prime[0] = 0;
    return prime;
}

vector<int> factors(int n) {
    vector<bool> prime = sieve(n + 1);
    vector<int> primelist;
    for (int i = 2; i <= n; i++) if (prime[i]) primelist.push_back(i);
    vector<int> facs;
    for (int i = 0; primelist[i] * primelist[i] <= n && i < primelist.size(); i++) {
        if (n % primelist[i] == 0) {
            while (n % primelist[i] == 0) {
                n /= primelist[i];
                facs.push_back(primelist[i]);
            }
        }
    }
    if (n > 1) facs.push_back(n);
    // sort(all(facs));
    return facs;
}

int gcdExtended(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int modInverse(int b, int m) {
    int x, y;
    int g = gcdExtended(b, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

int modDivide(int a, int b, int m) {
    a = a % m;
    int inv = modInverse(b, m);
    return (inv * a) % m;
}

// finds any solution of a Linear Diophantine Equation
bool lde(int a, int b, int c, int &x, int &y) {
    int d = gcdExtended(abs(a), abs(b), x, y);
    if (c % d) return false;
    x *= c / d;
    y *= c / d;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

int fact[MAX_N], invf[MAX_N];

void precompute_factorial() {
    fact[0] = invf[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        invf[i] = binpow(fact[i], MOD - 2, MOD); // Fermat's little theorem
    }
}

int nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invf[k] % MOD * invf[n - k] % MOD;

    // if there are only a few queries, then don't need to precompute invf[] => faster
    // return fact[n] * binpow(fact[k], MOD - 2, MOD) % MOD * binpow(fact[n - k], MOD - 2, MOD) % MOD;
}

int fac(int n) {
    if (n <= 1)
        return 1;
    return n * fac(n - 1);
}


// Z Algorithm
vector<int> calculateZ(string input) {
    vector<int> Z(input.size());
    int left = 0;
    int right = 0;
    for (int k = 1; k < input.size(); k++) {
        if (k > right) {
            left = right = k;
            while (right < input.size() && input[right] == input[right - left]) {
                right++;
            }
            Z[k] = right - left;
            right--;
        } else {
            //we are operating inside box
            int k1 = k - left;
            //if value does not stretches till right bound then just copy it.
            if (Z[k1] < right - k + 1) {
                Z[k] = Z[k1];
            } else { //otherwise try to see if there are more matches.
                left = k;
                while (right < input.size() && input[right] == input[right - left]) {
                    right++;
                }
                Z[k] = right - left;
                right--;
            }
        }
    }
    return Z;
}

// Returns list of all indices where pattern is found in text.
vector<int> matchPattern(string text, string pattern) {
    string newString = pattern + "$" + text;
    vector<int> result;
    vector<int> Z = calculateZ(newString);

    for (int i = 0; i < Z.size(); i++) {
        if (Z[i] == pattern.size()) {
            result.push_back(i - pattern.size() - 1);
        }
    }
    return result;
}
// Z algorithm ends



// KMP Algorithm
vector<int> computeTemporaryArray(string pattern) {  // function to find LPS array
    vector<int> lps(pattern.size());
    int index = 0;
    for (int i = 1; i < pattern.size();) {
        if (pattern[i] == pattern[index]) {
            lps[i] = index + 1;
            index++;
            i++;
        } else {
            if (index != 0) {
                index = lps[index - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

bool KMP(string text, string pattern) {

    vector<int> lps = computeTemporaryArray(pattern);
    int i = 0;
    int j = 0;
    while (i < text.size() && j < pattern.size()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    if (j == pattern.size()) {
        return true;
    }
    return false;
}

vector<int> KMP2(string text, string pattern) { // to find all occurences using kmp algo

    vector<int> lps = computeTemporaryArray(pattern);
    int i = 0;
    int j = 0;
    vector<int> result;
    while (i < text.size()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == pattern.size()) {
            result.push_back(i - j);
            //cout<<"Pattern is found at index "<<i-j<<"\n";
            j = lps[j - 1];
        } else if (i < text.size() && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return result;
}
// KMP Algorithm ends


// Graph 2 coloring using BFS
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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
    freopen("Error.txt", "w", stderr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
