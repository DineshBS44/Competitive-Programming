/*
 * AVL Tree Custom Implementation
 */

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
    int sumLeft;
    int sumRight;
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
    node->sumLeft = 0;
    node->sumRight = 0;
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    int ySumLeft = x->sumRight;

    int xSumRight = (ySumLeft + y->sumRight + (y->key * y->count) % MOD) % MOD;
    x->right = y;
    x->sumRight = xSumRight;

    y->left = T2;
    y->sumLeft = ySumLeft;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    y->size = size(y->left) + size(y->right) + y->count;
    x->size = size(x->left) + size(x->right) + x->count;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    int xSumRight = y->sumLeft;

    int ySumLeft = (x->sumLeft + xSumRight + (x->key * x->count) % MOD) % MOD;
    y->left = x;
    y->sumLeft = ySumLeft;

    x->right = T2;
    x->sumRight = xSumRight;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    x->size = size(x->left) + size(x->right) + x->count;
    y->size = size(y->left) + size(y->right) + y->count;

    return y;
}

int getBalance(Node *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, int key, int &countSmaller, int &countGreater, int &sumLarger, int &sumSmaller) {
    if (node == NULL) {
        return (newNode(key));
    }

    if (key < node->key) {
        node->left = insert(node->left, key, countSmaller, countGreater, sumLarger, sumSmaller);
        node->sumLeft = (((node->left->key) * (node->left->count)) % MOD +
                         ((node->left->sumRight) + (node->left->sumLeft)) % MOD) % MOD;
        countGreater = (countGreater + size(node->right) + node->count) % MOD;
        sumLarger = (sumLarger + (node->sumRight) + ((node->count) * (node->key)) % MOD) % MOD;
    } else if (key > node->key) {
        node->right = insert(node->right, key, countSmaller, countGreater, sumLarger, sumSmaller);
        node->sumRight = (((node->right->key) * (node->right->count)) % MOD +
                          ((node->right->sumRight) + (node->right->sumLeft)) % MOD) % MOD;
        countSmaller = (countSmaller + size(node->left) + node->count) % MOD;
        sumSmaller = (sumSmaller + (node->sumLeft) + ((node->count) * (node->key)) % MOD) % MOD;
    } else {
        countSmaller = (countSmaller + size(node->left)) % MOD;
        countGreater = (countGreater + size(node->right)) % MOD;
        sumLarger = (sumLarger + (node->sumRight)) % MOD;
        sumSmaller = (sumSmaller + (node->sumLeft)) % MOD;
        node->count++;
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    node->size = size(node->left) + size(node->right) + node->count;

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int solve(vector<int> &a, vector<int> &b) {
    int n = a.size();
    vector<int> pref1(n, 0), pref2(n, 0);
    int ans = 0;
    pref1[0] = a[0];
    pref2[0] = b[0];
    for (int i = 1; i < n; i++) {
        pref1[i] = (pref1[i - 1] + a[i]) % MOD;
        pref2[i] = (pref2[i - 1] + b[i]) % MOD;
    }
    Node *root1 = NULL, *root2 = NULL;
    for (int i = 0; i < n; i++) {
        if (a[i] <= b[i]) {
            int len = i + 1;
            int diff = b[i] - a[i];
            int smaller = 0, greater = 0, sumLarger = 0, sumSmaller = 0;
            root2 = insert(root2, diff, smaller, greater, sumLarger, sumSmaller);
            int sum = (pref1[i] + sumLarger) % MOD;
            sum = (sum + (a[i] * greater) % MOD) % MOD;
            sum = (sum + ((i + 1 - greater) * b[i]) % MOD) % MOD;
            sum = (sum * 2) % MOD;
            sum = (sum - (a[i] + b[i]) % MOD) % MOD;
            ans = (ans + sum) % MOD;
        } else {
            int len = i + 1;
            int diff = a[i] - b[i];
            int smaller = 0, greater = 0, sumLarger = 0, sumSmaller = 0;
            root1 = insert(root1, diff, smaller, greater, sumLarger, sumSmaller);
            int sum = (pref2[i] + sumLarger) % MOD;
            sum = (sum + (b[i] * greater) % MOD) % MOD;
            sum = (sum + ((i + 1 - greater) * a[i]) % MOD) % MOD;
            sum = (sum * 2) % MOD;
            sum = (sum - (a[i] + b[i]) % MOD) % MOD;
            ans = (ans + sum) % MOD;
        }
    }
    int res = ans % MOD;
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    cout << "ans: " << solve(a, b) << "\n";

    return 0;
}

/*
9
10 8 7 1 10 1 9 4 9
9 2 7 1 4 3 6 4 8
Ans: 1041
*/

/*
10
8 3 2 2 4 2 3 2 4 2
9 9 5 10 1 9 5 2 2 9
Ans: 1143
*/
