#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    Node* left;
    Node* right;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
    }
};

class Dictionary {
    Node* root;

    Node* insert(Node* root, string k, string m) {
        if (root == nullptr)
            return new Node(k, m);

        if (k < root->keyword)
            root->left = insert(root->left, k, m);
        else if (k > root->keyword)
            root->right = insert(root->right, k, m);
        else
            cout << "Keyword already exists.\n";
        return root;
    }

    Node* findMin(Node* root) {
        while (root && root->left)
            root = root->left;
        return root;
    }

    Node* deleteNode(Node* root, string k) {
        if (!root) return nullptr;

        if (k < root->keyword)
            root->left = deleteNode(root->left, k);
        else if (k > root->keyword)
            root->right = deleteNode(root->right, k);
        else {
            // Node found
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            } else if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            } else {
                Node* temp = findMin(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }
        return root;
    }

    Node* update(Node* root, string k, string newMeaning) {
        if (!root)
            return nullptr;
        if (k < root->keyword)
            root->left = update(root->left, k, newMeaning);
        else if (k > root->keyword)
            root->right = update(root->right, k, newMeaning);
        else
            root->meaning = newMeaning;
        return root;
    }

    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->keyword << ": " << root->meaning << endl;
        inorder(root->right);
    }

    void reverseInorder(Node* root) {
        if (!root) return;
        reverseInorder(root->right);
        cout << root->keyword << ": " << root->meaning << endl;
        reverseInorder(root->left);
    }

    int maxComparisons(Node* root) {
        if (!root) return 0;
        return 1 + max(maxComparisons(root->left), maxComparisons(root->right));
    }

    bool search(Node* root, string k, int& count) {
        if (!root) return false;
        count++;
        if (k == root->keyword)
            return true;
        else if (k < root->keyword)
            return search(root->left, k, count);
        else
            return search(root->right, k, count);
    }

public:
    Dictionary() {
        root = nullptr;
    }

    void addKeyword(string k, string m) {
        root = insert(root, k, m);
    }

    void deleteKeyword(string k) {
        root = deleteNode(root, k);
    }

    void updateMeaning(string k, string newMeaning) {
        if (update(root, k, newMeaning))
            cout << "Updated successfully.\n";
        else
            cout << "Keyword not found.\n";
    }

    void displayAscending() {
        cout << "Dictionary (Ascending Order):\n";
        inorder(root);
    }

    void displayDescending() {
        cout << "Dictionary (Descending Order):\n";
        reverseInorder(root);
    }

    void findMaxComparisons() {
        cout << "Maximum comparisons (tree height): " << maxComparisons(root) << endl;
    }

    void searchKeyword(string k) {
        int count = 0;
        if (search(root, k, count))
            cout << "Keyword found in " << count << " comparisons.\n";
        else
            cout << "Keyword not found after " << count << " comparisons.\n";
    }
};

// --- MAIN ---
int main() {
    Dictionary dict;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary Operations:\n";
        cout << "1. Add Keyword\n2. Delete Keyword\n3. Update Meaning\n";
        cout << "4. Display Ascending\n5. Display Descending\n";
        cout << "6. Max Comparisons\n7. Search Keyword\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.addKeyword(key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dict.deleteKeyword(key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dict.updateMeaning(key, meaning);
                break;
            case 4:
                dict.displayAscending();
                break;
            case 5:
                dict.displayDescending();
                break;
            case 6:
                dict.findMaxComparisons();
                break;
            case 7:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                dict.searchKeyword(key);
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
