#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool rightThread;  // true if right is a thread (in-order successor)

    Node(int val) {
        data = val;
        left = right = nullptr;
        rightThread = false;
    }
};

// Insert nodes like a regular binary search tree
Node* insert(Node* root, int key) {
    if (!root)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// Converts to in-order threaded binary tree
void createThreaded(Node* root, Node*& prev) {
    if (!root) return;

    createThreaded(root->left, prev);

    if (prev && !prev->right) {
        prev->right = root;
        prev->rightThread = true;
    }

    prev = root;
    createThreaded(root->right, prev);
}

// Find leftmost node
Node* leftmost(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// In-order traversal of threaded binary tree
void inorderThreaded(Node* root) {
    Node* curr = leftmost(root);
    while (curr) {
        cout << curr->data << " ";

        if (curr->rightThread)
            curr = curr->right;
        else
            curr = leftmost(curr->right);
    }
}

int main() {
    Node* root = nullptr;

    // Constructing binary tree
    root = insert(root, 20);
    insert(root, 10);
    insert(root, 30);
    insert(root, 5);
    insert(root, 15);
    insert(root, 25);
    insert(root, 35);

    // Convert to threaded tree
    Node* prev = nullptr;
    createThreaded(root, prev);

    cout << "In-order traversal of threaded binary tree:\n";
    inorderThreaded(root);

    return 0;
}
