#include<bits/stdc++.h>

using namespace std;

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

Node *insert(Node *node, int key, int &count) {
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key, count);
    else if (key > node->key) {
        node->right = insert(node->right, key, count);

        count = count + size(node->left) + node->count;
    } else {
        count = count + size(node->left);
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

void constructLowerArray(vector<int> &arr, vector<int> &countSmaller, int n) {
    int i, j;
    Node *root = NULL;

    for (i = 0; i < n; i++)
        countSmaller[i] = 0;

    for (i = n - 1; i >= 0; i--) {
        root = insert(root, arr[i], countSmaller[i]);
    }
}

void printArray(vector<int> &arr, int size) {
    int i;
    cout << "\n";
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
}

int main() {
    vector<int> arr = {10, 6, 15, 20, 30, 5, 5, 7};
    int n = arr.size();
    vector<int> low(n);
    constructLowerArray(arr, low, n);
    cout << "Following is the constructed smaller count array";
    printArray(low, n);

    return 0;
}