#include<bits/stdc++.h>

using namespace std;

int ans = 0;

struct Tree {
    Tree *left;
    Tree *right;
    int val;
    int maxDown, maxUp;
    Tree() : val(0), left(nullptr), right(nullptr), maxUp(0), maxDown(0) {}
    Tree(int x) : val(x), left(nullptr), right(nullptr), maxUp(0), maxDown(0) {}
};

void dfs(Tree *node) {
    if (node == NULL) return;
    dfs(node->left);
    dfs(node->right);
    int maxDownLeft = 0, maxDownRight = 0;
    int maxUpRight = 0, maxUpLeft = 0;
    int maxUp = 0, maxDown = 0;
    if (node->left) {
        maxUpLeft = node->left->maxUp;
        maxDownLeft = node->left->maxDown;
    }
    if (node->right) {
        maxUpRight = node->right->maxUp;
        maxDownRight = node->right->maxDown;
    }
    if (node->left && node->left->val > node->val) {
        maxDown = maxDownLeft;
    }
    if (node->right && node->right->val > node->val) {
        maxDown = max(maxDown, maxDownRight);
    }

    if (node->left && node->left->val < node->val) {
        maxUp = maxUpLeft;
    }
    if (node->right && node->right->val < node->val) {
        maxUp = max(maxUp, maxUpRight);
    }
    cout << "node->val is " << node->val << "\n";
    cout << "maxDownLeft: " << maxDownLeft << " maxDownRight: " << maxDownRight << "\n";
    cout << "maxUpLeft: " << maxUpLeft << " maxUpRight: " << maxUpRight << "\n";
    cout << "maxDown: " << maxDown << " maxUp: " << maxUp << "\n";
    node->maxUp = maxUp + 1;
    node->maxDown = maxDown + 1;
    cout << "node->maxDown: " << node->maxDown << " node->maxUp: " << node->maxUp << "\n";
    ans = max(ans, maxUp + maxDown + 1);
    cout << "\n";
}

int findMaxLength(Tree *root) {
    ans = 0;
    dfs(root);
    return ans;
}

int main() {
    Tree *root = new Tree(3);
    root->left = new Tree(1);
    root->right = new Tree(4);
    cout << findMaxLength(root) << "\n";
}
