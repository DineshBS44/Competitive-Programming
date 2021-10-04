#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
};

static Node *prevNode = NULL;

void BinaryTree2DoubleLinkedList(Node *node, Node *&head) {
    if (node == NULL) return;

    BinaryTree2DoubleLinkedList(node->left, head);

    if (prevNode == NULL)
        head = node;
    else {
        node->left = prevNode;
        prevNode->right = node;
    }
    prevNode = node;

    BinaryTree2DoubleLinkedList(node->right, head);
}

Node *newNode(int data) {
    Node *new_node = new Node();
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return (new_node);
}

void printList(Node *node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->right;
    }
}

int main() {
    Node *root = newNode(10);
    root->left = newNode(12);
    root->right = newNode(15);
    root->left->left = newNode(25);
    root->left->right = newNode(30);
    root->right->left = newNode(36);

    Node *head = NULL;
    BinaryTree2DoubleLinkedList(root, head);

    printList(head);

    return 0;
}