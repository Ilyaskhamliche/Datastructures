#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

void bfs(int start, vector<vector<int>>& graph, unordered_set<int>& visited) {
    queue<int> queue;
    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        cout << current << " ";

        for (int neighbor : graph[current]) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }
}

int main() {
    int numVertices = 5;
    vector<vector<int>> graph(numVertices);

    // Add edges
    graph[0] = {1, 4};
    graph[1] = {0, 2, 3, 4};
    graph[2] = {1, 3};
    graph[3] = {1, 2, 4};
    graph[4] = {0, 1, 3};

    unordered_set<int> visited;
    cout << "Breadth-First Traversal (starting from vertex 0): ";
    bfs(0, graph, visited);
    cout << endl;

    return 0;
}
