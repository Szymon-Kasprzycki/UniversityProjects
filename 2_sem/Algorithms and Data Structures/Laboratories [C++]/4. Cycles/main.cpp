#include <iostream>

using namespace std;

bool has_cycle(int **adj, int n) {
    // Cycle must have at least 3 vertices
    if (n < 3) return false; 

    int *degree = new int[n];
    for (int i = 0; i < n; ++i) degree[i] = 0;

    // Calculate degree of each vertex (number of edges)
    for (int i = 0; i < (n*n); ++i) degree[i/n] += adj[i/n][i%n];

    // Check if all vertices have degree 2, because if not, there is no cycle
    for (int i = 0; i < n; ++i) if (degree[i] != 2) return false;

    // Prepare structures for DFS algorithm
    bool *visited = new bool[n];
    for (int i = 0; i < n; ++i) visited[i] = false;
    visited[0] = true;
    int count = 1, current = 0;

    // DFS algorithm
    while (count < n) {
        bool found = false;
        // Find next vertex to visit
        for (int i = 0; i < n; ++i)
        {
            // If there is an edge from current vertex to i and i has not been visited
            if (adj[current][i] && !visited[i])
            {
                // Visit i
                visited[i] = true;
                ++count;
                // Update current vertex
                current = i;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

    delete[] degree;
    delete[] visited;
    return true;
}

int main() {
    int t;
    cin >> t;

    while (t>0) {
        int n;
        cin >> n;
        int **adj = new int*[n];
        for (int i = 0; i < n; i++) adj[i] = new int[n];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                char c;
                cin >> c;
                adj[i][j] = c - '0';
            }
        cout << has_cycle(adj, n) << '\n';
        for (int i = 0; i < n; i++) delete[] adj[i];
        delete[] adj;
        --t;
    }

    return 0;
}