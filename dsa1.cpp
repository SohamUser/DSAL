#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Insert a node into BST
Node* insert(Node* root, int val) {
    if (root == nullptr)
        return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Find longest path from root (i.e., height of tree)
int findLongestPath(Node* root) {
    if (root == nullptr)
        return 0;
    int leftHeight = findLongestPath(root->left);
    int rightHeight = findLongestPath(root->right);
    return 1 + max(leftHeight, rightHeight);
}

// Find minimum data value in BST
int findMin(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return -1;
    }
    while (root->left != nullptr)
        root = root->left;
    return root->data;
}

// Mirror the tree
void mirrorTree(Node* root) {
    if (root == nullptr)
        return;
    // Swap left and right
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Search a value in BST
bool search(Node* root, int key) {
    if (root == nullptr)
        return false;
    if (key == root->data)
        return true;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Inorder traversal (for checking)
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    // Construct BST from values
    for (int val : values)
        root = insert(root, val);

    cout << "Inorder traversal of the original tree:\n";
    inorder(root);
    cout << endl;

    // Insert a new node
    int newVal = 65;
    root = insert(root, newVal);
    cout << "Inorder after inserting " << newVal << ":\n";
    inorder(root);
    cout << endl;

    // Longest path (height)
    cout << "Number of nodes in longest path from root: " << findLongestPath(root) << endl;

    // Minimum value
    cout << "Minimum value in the BST: " << findMin(root) << endl;

    // Mirror the tree
    mirrorTree(root);
    cout << "Inorder traversal after mirroring the tree:\n";
    inorder(root);
    cout << endl;

    // Search for a value
    int searchVal = 40;
    if (search(root, searchVal))
        cout << "Value " << searchVal << " found in the BST.\n";
    else
        cout << "Value " << searchVal << " not found in the BST.\n";

    return 0;
}
