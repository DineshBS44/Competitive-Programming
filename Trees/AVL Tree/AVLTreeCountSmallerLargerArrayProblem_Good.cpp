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

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    int size;
    int count;
};

int height(Node *N) {
    if (N == NULL) return 0;
    return N->height;
}

int size(Node *N) {
    if (N == NULL) return 0;
    return N->size;
}

Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->size = 1;
    node->count = 1;
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    y->size = size(y->left) + size(y->right) + y->count;
    x->size = size(x->left) + size(x->right) + x->count;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    x->size = size(x->left) + size(x->right) + x->count;
    y->size = size(y->left) + size(y->right) + y->count;

    return y;
}

int getBalance(Node *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, int key, int &countSmaller, int &countGreater) {
    if (node == NULL)
        return (newNode(key));

    if (key < node->key) {
        node->left = insert(node->left, key, countSmaller, countGreater);

        countGreater = countGreater + size(node->right) + node->count;
    } else if (key > node->key) {
        node->right = insert(node->right, key, countSmaller, countGreater);

        countSmaller = countSmaller + size(node->left) + node->count;
    } else {
        countSmaller = countSmaller + size(node->left);
        countGreater = countGreater + size(node->right);
        node->count++;
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    node->size = size(node->left) + size(node->right) + node->count;

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void constructArray(vector<int> &arr, vector<int> &countSmaller, vector<int> &countGreater, int n) {
    int i, j;
    Node *root = NULL;

    for (i = 0; i < n; i++) {
        countSmaller[i] = 0;
        countGreater[i] = 0;
    }

    for (i = 0; i < n; i++) {
        root = insert(root, arr[i], countSmaller[i], countGreater[i]);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> smaller(n), greater(n);
    constructArray(a, smaller, greater, n);

    deque<int> dq;
    dq.pb(a[0]);
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] <= dq.front()) {
            dq.push_front(a[i]);
            ans += smaller[i];

        } else if (a[i] >= dq.back()) {
            dq.push_back(a[i]);
            ans += greater[i];
        } else {
            if (smaller[i] > greater[i]) {
                dq.pb(a[i]);
                ans += greater[i];
            } else {
                dq.push_front(a[i]);
                ans += smaller[i];
            }
        }
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