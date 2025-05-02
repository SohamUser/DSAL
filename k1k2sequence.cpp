#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define INF INT_MAX

// Function to build optimal BST
void optimalBST(const vector<double>& p, int n) {
    vector<vector<double>> cost(n + 2, vector<double>(n + 1, 0));
    vector<vector<int>> root(n + 2, vector<int>(n + 1, 0));
    vector<vector<double>> weight(n + 2, vector<double>(n + 1, 0));

    // Initialize for empty trees
    for (int i = 1; i <= n + 1; ++i) {
        cost[i][i - 1] = 0;
        weight[i][i - 1] = 0;
    }

    // L is the chain length
    for (int L = 1; L <= n; ++L) {
        for (int i = 1; i <= n - L + 1; ++i) {
            int j = i + L - 1;
            cost[i][j] = INF;
            weight[i][j] = weight[i][j - 1] + p[j];

            for (int r = i; r <= j; ++r) {
                double temp_cost = cost[i][r - 1] + cost[r + 1][j] + weight[i][j];
                if (temp_cost < cost[i][j]) {
                    cost[i][j] = temp_cost;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "\nMinimum cost of Optimal BST: " << cost[1][n] << endl;

    // Function to print tree structure
    function<void(int, int, int)> printTree = [&](int i, int j, int parent) {
        if (i > j)
            return;
        int r = root[i][j];
        if (parent == -1)
            cout << "Root: k" << r << endl;
        else if (r < parent)
            cout << "Left child of k" << parent << ": k" << r << endl;
        else
            cout << "Right child of k" << parent << ": k" << r << endl;
        printTree(i, r - 1, r);
        printTree(r + 1, j, r);
    };

    cout << "\nOptimal BST structure:\n";
    printTree(1, n, -1);
}

int main() {
    // Sorted keys: k1 < k2 < ... < kn
    // Probabilities p[1..n]
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<double> p(n + 1); // 1-based indexing
    cout << "Enter search probabilities for keys:\n";
    for (int i = 1; i <= n; ++i) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    optimalBST(p, n);
    return 0;
}
