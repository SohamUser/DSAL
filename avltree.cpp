#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    Node *left, *right;
    int height;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotate Right
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// Rotate Left
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Insert
Node* insert(Node* root, string keyword, string meaning) {
    if (!root) return new Node(keyword, meaning);
    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else {
        cout << "Keyword already exists.\n";
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance the tree
    if (balance > 1 && keyword < root->left->keyword)
        return rotateRight(root);
    if (balance < -1 && keyword > root->right->keyword)
        return rotateLeft(root);
    if (balance > 1 && keyword > root->left->keyword) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && keyword < root->right->keyword) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Find minimum node
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

// Delete
Node* deleteNode(Node* root, string keyword) {
    if (!root) return root;

    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance tree
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Search and count comparisons
int search(Node* root, string keyword, int& comparisons) {
    if (!root) return 0;
    comparisons++;
    if (keyword == root->keyword) {
        cout << "Meaning: " << root->meaning << endl;
        return 1;
    }
    if (keyword < root->keyword)
        return search(root->left, keyword, comparisons);
    else
        return search(root->right, keyword, comparisons);
}

// Update
bool update(Node* root, string keyword, string newMeaning) {
    if (!root) return false;
    if (keyword == root->keyword) {
        root->meaning = newMeaning;
        return true;
    }
    if (keyword < root->keyword)
        return update(root->left, keyword, newMeaning);
    else
        return update(root->right, keyword, newMeaning);
}

// Inorder (Ascending)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->keyword << ": " << root->meaning << endl;
        inorder(root->right);
    }
}

// Reverse Inorder (Descending)
void reverseInorder(Node* root) {
    if (root) {
        reverseInorder(root->right);
        cout << root->keyword << ": " << root->meaning << endl;
        reverseInorder(root->left);
    }
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert\n2. Delete\n3. Update\n4. Search\n5. Display Ascending\n6. Display Descending\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword and meaning: ";
                cin >> key >> meaning;
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin >> meaning;
                if (update(root, key, meaning))
                    cout << "Updated successfully.\n";
                else
                    cout << "Keyword not found.\n";
                break;
            case 4: {
                int comparisons = 0;
                cout << "Enter keyword to search: ";
                cin >> key;
                if (!search(root, key, comparisons))
                    cout << "Keyword not found.\n";
                cout << "Comparisons made: " << comparisons << endl;
                break;
            }
            case 5:
                cout << "Dictionary in Ascending Order:\n";
                inorder(root);
                break;
            case 6:
                cout << "Dictionary in Descending Order:\n";
                reverseInorder(root);
                break;
        }
    } while (choice != 0);

    return 0;
}
