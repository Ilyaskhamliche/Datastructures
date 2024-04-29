#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to remove the edge between two vertices
void removeEdge(vector<vector<int>>& graph, int u, int v) {
    graph[u][v] = 0;
    graph[v][u] = 0;
}

// Function to check if a vertex is eligible for the circuit
bool isEligible(vector<vector<int>>& graph, int u, int n) {
    int count = 0;
    for (int v = 0; v < n; v++) {
        if (graph[u][v])
            count++;
    }
    return (count % 2 == 0);
}

// Function to find the Eulerian circuit using Fleury's algorithm
vector<int> findEulerianCircuit(vector<vector<int>>& graph, int n) {
    vector<int> circuit;
    if (!isEligible(graph, 0, n))
        return circuit;  // No Eulerian circuit exists

    // Start the circuit from vertex 0
    circuit.push_back(0);
    int currentVertex = 0;

    // Iterate until the circuit is complete
    while (!circuit.empty()) {
        if (isEligible(graph, currentVertex, n)) {
            // Move to the next eligible vertex
            int nextVertex = -1;
            for (int v = 0; v < n; v++) {
                if (graph[currentVertex][v]) {
                    nextVertex = v;
                    break;
                }
            }
            if (nextVertex == -1)
                break;  // The circuit is complete

            circuit.push_back(nextVertex);
            removeEdge(graph, currentVertex, nextVertex);
            currentVertex = nextVertex;
        } else {
            // Backtrack to the previous vertex
            currentVertex = circuit.back();
            circuit.pop_back();
        }
    }

    return circuit;
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    vector<int> circuit = findEulerianCircuit(graph, n);

    if (circuit.empty()) {
        cout << "No Eulerian circuit exists in the given graph.\n";
    } else {
        cout << "The Eulerian circuit is: ";
        for (int vertex : circuit) {
            cout << vertex << " ";
        }
        cout << "\n";
    }

    return 0;
}
