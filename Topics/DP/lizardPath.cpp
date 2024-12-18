#include<algorithm>
#include<chrono>
#include<iostream>
#include<list>
#include<tuple>
#include<queue>
#include<set>
#include<limits>
using namespace std;
/*
4*5 example: 
1 2 4 3 6
2 4 6 2 3
4 4 3 1 2
1 2 5 4 6

*/
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
};
class FindPath {
    public:
        int x;
        int y;
        vector<vector<int>> board;
        FindPath(int x, int y, vector<vector<int>> board) {
            this->x = x;
            this->y = y;
            this->board = board;
        }
        static int indexing(int i, int j, int y) {
            return i * y + j;
        }
        int naiveFind() {
            return 0;
        }
        int naiveGraphFind() {
            int size = x * y;
            Graph *g = new Graph(size + 2);
            g->addNode(size + 1);
            for (int i = 0; i < x - 1; i++) {
                for (int j = 0; j < y; j++) {
                    int idx = indexing(i,j,y);
                    cout<< "intering"<<j<<endl;
                    g->addNode(idx);
                    cout<< i<<", "<<j<<endl;

                    if (i == 0) {
                        g->addEdgeList(size + 1, idx, board[i][j]);
                    } else {
                        if (j == 0) {
                            g->addEdgeList(indexing(i - 1, j, y), indexing(i, j, y), board[i][j]);
                            g->addEdgeList(indexing(i - 1, j + 1, y), indexing(i, j, y), board[i][j]);
                        } else if (j == y - 1) {
                            g->addEdgeList(indexing(i - 1, j - 1, y), indexing(i, j, y), board[i][j]);
                            g->addEdgeList(indexing(i - 1, j, y), indexing(i, j, y), board[i][j]);
                        } else {
                            g->addEdgeList(indexing(i - 1, j - 1, y), indexing(i, j, y), board[i][j]);
                            g->addEdgeList(indexing(i - 1, j, y), indexing(i, j, y), board[i][j]);
                            g->addEdgeList(indexing(i - 1, j + 1, y), indexing(i, j, y), board[i][j]);
                        }
                    }
                    cout<<"finishing "<< i << endl;
                }
            }
            for (int k = 0; k < y; k++) {
                g->addEdgeList(indexing(x - 1, k, y), size, 0);
            }
            g->printGraph();
            return g->dijkstra(size + 1, size);
            // populated the graph
        }

};

int main() {
        vector<vector<int>> board = {
        {1, 2, 4, 3, 6},
        {2, 4, 6, 2, 3},
        {4, 4, 3, 1, 2},
        {1, 2, 5, 4, 6}
    };
    
    // Initialize FindPath with dimensions of the board and the board itself
    FindPath fp(4, 5, board);
    
    // Call naiveGraphFind to get the shortest path from the top to the bottom
    int result = fp.naiveGraphFind();
    
    // Print the result
    cout << "Shortest path weight: " << result << endl;
    
    return 0;
}