#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    // Enqueue the start node and mark it as visited
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        // Visit all adjacent nodes of the current node
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                // Enqueue unvisited neighbors and mark them as visited
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    cout << endl;
}

int main() {
    // // Example graph represented as an adjacency list
    // vector<vector<int>> graph = {
    //     {1, 2},     // Node 0 is connected to nodes 1 and 2
    //     {0, 3, 4},  // Node 1 is connected to nodes 0, 3, and 4
    //     {0, 5, 6},  // Node 2 is connected to nodes 0, 5, and 6
    //     {1},        // Node 3 is connected to node 1
    //     {1},        // Node 4 is connected to node 1
    //     {2},        // Node 5 is connected to node 2
    //     {2}         // Node 6 is connected to node 2
    // };

    // int startNode = 0;  // Starting BFS from node 0
    // bfs(graph, startNode);
int init_graph[10][10] = {  {0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
				    {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
				    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
				    {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
				    {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
				    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0} };
	int n = 10;
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (init_graph[i][j]) graph[i].push_back(j);
		}
	}

	bfs(graph, 0);
    return 0;
}
