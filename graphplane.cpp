#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Graph {
    int V;
    map<string, int> cityIndex; // Map city name to index
    vector<string> indexCity;   // Map index to city name
    vector<vector<pair<int, int>>> adjList; // city -> (neighborIndex, cost)

public:
    Graph(int v) {
        V = v;
        adjList.resize(v);
        indexCity.resize(v);
    }

    void addCity(int idx, string cityName) {
        cityIndex[cityName] = idx;
        indexCity[idx] = cityName;
    }

    void addFlight(string from, string to, int cost) {
        int u = cityIndex[from];
        int v = cityIndex[to];
        adjList[u].push_back({v, cost});
        adjList[v].push_back({u, cost}); // Assuming undirected (bidirectional) flights
    }

    void display() {
        cout << "\nFlight Map (Adjacency List):\n";
        for (int i = 0; i < V; i++) {
            cout << indexCity[i] << " -> ";
            for (auto p : adjList[i]) {
                cout << "(" << indexCity[p.first] << ", Cost: " << p.second << ") ";
            }
            cout << "\n";
        }
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        for (auto p : adjList[v]) {
            if (!visited[p.first]) {
                DFSUtil(p.first, visited);
            }
        }
    }

    bool isConnected() {
        vector<bool> visited(V, false);
        DFSUtil(0, visited);

        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }
};

// --- MAIN ---
int main() {
    int numCities = 5;
    Graph g(numCities);

    // Add cities
    g.addCity(0, "Mumbai");
    g.addCity(1, "Delhi");
    g.addCity(2, "Chennai");
    g.addCity(3, "Kolkata");
    g.addCity(4, "Bangalore");

    // Add flights (cost can be time in mins or fuel in liters)
    g.addFlight("Mumbai", "Delhi", 120);
    g.addFlight("Mumbai", "Bangalore", 100);
    g.addFlight("Delhi", "Kolkata", 150);
    g.addFlight("Bangalore", "Chennai", 90);
    g.addFlight("Chennai", "Kolkata", 110);

    g.display();

    if (g.isConnected())
        cout << "\nThe graph is CONNECTED: All cities are reachable from any city.\n";
    else
        cout << "\nThe graph is NOT connected: Some cities are not reachable.\n";

    return 0;
}
