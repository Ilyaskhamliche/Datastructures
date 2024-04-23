#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

void dfs(int start, vector<vector<int>>& graph, unordered_set<int>& visited) {
    stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        if (visited.count(current) == 0) {
            visited.insert(current);
            cout << current << " ";

            for (int neighbor : graph[current]) {
                if (visited.count(neighbor) == 0) {
                    stack.push(neighbor);
                }
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
    cout << "Depth-First Traversal (starting from vertex 0): ";
    dfs(0, graph, visited);
    cout << endl;

    return 0;
}
