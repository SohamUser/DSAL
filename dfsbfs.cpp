#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// Number of landmarks (nodes)
const int NUM_NODES = 6;

// Mapping index to landmark name
map<int, string> landmark = {
    {0, "College Gate"},
    {1, "Library"},
    {2, "Canteen"},
    {3, "Hostel"},
    {4, "Playground"},
    {5, "Parking Lot"}
};

// DFS using adjacency matrix
void DFS(int node, const vector<vector<int>>& adjMatrix, vector<bool>& visited) {
    visited[node] = true;
    cout << landmark[node] << " -> ";

    for (int i = 0; i < NUM_NODES; ++i) {
        if (adjMatrix[node][i] == 1 && !visited[i]) {
            DFS(i, adjMatrix, visited);
        }
    }
}

// BFS using adjacency list
void BFS(int start, const vector<vector<int>>& adjList) {
    vector<bool> visited(NUM_NODES, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << landmark[node] << " -> ";

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    // Adjacency Matrix (6x6 initialized to 0)
    vector<vector<int>> adjMatrix(NUM_NODES, vector<int>(NUM_NODES, 0));

    // Adjacency List
    vector<vector<int>> adjList(NUM_NODES);

    // Define edges between landmarks (undirected)
    vector<pair<int, int>> edges = {
        {0, 1}, // College Gate - Library
        {0, 2}, // College Gate - Canteen
        {1, 3}, // Library - Hostel
        {2, 4}, // Canteen - Playground
        {3, 5}, // Hostel - Parking Lot
        {4, 5}  // Playground - Parking Lot
    };

    // Build the graph
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;

        // Add to matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // Add to list
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    cout << "DFS Traversal using Adjacency Matrix:\n";
    vector<bool> visited(NUM_NODES, false);
    DFS(0, adjMatrix, visited);

    cout << "\n\nBFS Traversal using Adjacency List:\n";
    BFS(0, adjList);

    return 0;
}
