#include<bits/stdc++.h>

using namespace std;


const int INF = 1e9; // INF = 1B, not 2^31-1 to avoid overflow
class Graph {
private:
    int size;
    vector<int> nodes;  // List of nodes in the graph
    vector<tuple<int, int, int>> edges;  // List of edges (src, dest, weight)
    vector<vector<pair<int, int>>> adjList;  // Adjacency list (node -> [(dest, weight)])

public:
    // Constructor to initialize with nodes
    Graph(vector<int> nodes) {
        this->size = nodes.size();
        this->nodes = nodes;
        adjList.resize(size);
    }

    // Constructor to initialize with size
    Graph(int size) {
        this->size = size;
        adjList.resize(size);
    }

    // Add a node (if not exceeding the graph size)
    void addNode(int node) {
        if (this->nodes.size() >= this->size) {
            return;
        }
        this->nodes.push_back(node);
    }

    // Add an edge between nodes with weight
    void addEdge(int src, int dest, int weight) {
        this->edges.push_back(make_tuple(src, dest, weight));
    }

    // Add an edge to the adjacency list (src -> dest with weight)
    void addEdgeList(int src, int dest, int weight) {
        this->adjList[src].push_back(make_pair(dest, weight));
        this->adjList[dest].push_back(make_pair(src, weight));
        cout<< "adding: "<< src << " --> " << dest<<" weight: "<< weight <<endl;
    }
    void addEdgeListDirected(int src, int dest, int weight) {
        this->adjList[src].push_back(make_pair(dest, weight));
        cout<< "adding: "<< src << " --> " << dest<<" weight: "<< weight <<endl;
    }
    void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
            cout<<"Node " <<i<<": ";
            for (int j = 0; j < adjList[i].size(); j++) {
                cout << adjList[i][j].first << ", ";
            }
            cout<<endl;
        }
    }
    // Dijkstra's algorithm to find shortest path from 'start' to 'end'
    int dijkstra(int start, int end) {
        vector<int> distance(size, INF);  // Initialize all distances as INF
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Start from the 'start' node
        distance[start] = 0;
        pq.push({0, start});  // Push the starting node with distance 0

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // If we reach the 'end' node, return the distance
            if (u == end) {
                return currentDist;
            }

            // Process each neighbor of the current node
            for (const auto& neighbor : adjList[u]) {
                int v = get<0>(neighbor);  // Destination node
                int weight = get<1>(neighbor);  // Edge weight

                // Relax the edge
                if (currentDist + weight < distance[v]) {
                    distance[v] = currentDist + weight;
                    pq.push({distance[v], v});
                }
            }
        }

        return INF;  // If there's no path from start to end
    }
    int bellman_ford(int start, int end) {
        // use addEdge
        vector<int> dist(size, INF);
        dist[start] = 0;
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < edges.size(); j++) {
                int src = get<0>(edges[j]);
                int dest = get<1>(edges[j]);
                int weight = get<2>(edges[j]);
                if (dist[src] != INF && dist[src] + weight < dist[dest]) {
                    if (i == nodes.size() - 1) {
                        return -1; // negative cycle detected
                    }
                    dist[dest] = dist[src] + weight;
                }
            }
        }
        return dist[end];
    }
};

int main() {
    // Create a graph with 5 nodes (0 to 4)
    Graph g(5);

    // Add edges (directed with weights)
    g.addEdgeListDirected(0, 1, 1);
    g.addEdgeListDirected(0, 2, 5);
    g.addEdgeListDirected(1, 2, 2);
    g.addEdgeListDirected(1, 3, 1);
    g.addEdgeListDirected(2, 1, 3);
    g.addEdgeListDirected(2, 3, 9);
    g.addEdgeListDirected(2, 4, 2);
    g.addEdgeListDirected(3, 4, 4);

    // Call Dijkstra's algorithm to find the shortest path from node 0 to node 4
    int result = g.dijkstra(0, 4);
    int result2 = g.bellman_ford(0, 4);
    // Output the result
    cout << "Shortest path from 0 to 4: (Dijkstra)" << result << endl;
    cout << "Shortest path from 0 to 4: (Bellman ford)" << result2 << endl;

    return 0;
}