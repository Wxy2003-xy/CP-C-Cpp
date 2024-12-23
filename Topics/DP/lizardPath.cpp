#include<algorithm>
#include<chrono>
#include<iostream>
#include<list>
#include<tuple>
#include<queue>
#include<set>
#include<limits>
using namespace std;
using namespace chrono;
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
    }
    void addEdgeListDirected(int src, int dest, int weight) {
        this->adjList[src].push_back(make_pair(dest, weight));
    }
    void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
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
            for (int i = 0; i < y; i++) {
                g->addEdgeListDirected(size+1, i, 0);
            }
            for (int i = 0; i < x - 1; i++) {
                for (int j = 0; j < y; j++) {
                    g->addEdgeListDirected(indexing(i, j, y), indexing(i + 1, j, y), board[i][j]);
                    if (j != 0) {
                        g->addEdgeListDirected(indexing(i, j, y), indexing(i + 1, j - 1, y), board[i][j]);
                    }
                    if (j != y - 1) {
                        g->addEdgeListDirected(indexing(i, j, y), indexing(i + 1, j + 1, y), board[i][j]);
                    }
                }
            }
            for (int j = 0; j < y; j++) {
                g->addEdgeListDirected(indexing(x-1, j, y), size, board[x-1][j]);
            }
            // g->printGraph();
            return g->dijkstra(size + 1, size);
            // populated the graph
        }
        int dp_solution() {
            int memo[x][y];
            for (int i = 0; i < y; i++) {
                memo[0][i] = board[0][i];
            }
            for (int i = 1; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    if (j == 0) {
                        memo[i][j] = min(memo[i - 1][j + 1], memo[i - 1][j]) + board[i][j];
                        continue;
                    }
                    if (j == y - 1) {
                        memo[i][j] = min(memo[i - 1][j - 1], memo[i - 1][j]) + board[i][j];
                        continue;
                    }
                    int m = min(min(memo[i - 1][j - 1], memo[i - 1][j]), memo[i - 1][j + 1]);
                    memo[i][j] = m + board[i][j];
                }
            }
            int ans = 1e9;
            for (int i = 0; i < y; i++) {
                ans = min(ans, memo[x - 1][i]);
            }
            // for (int i = 0; i < x; i++) {
            //     for (int j = 0; j < y; j++) {
            //         cout<<memo[i][j]<<" ";
            //     }
            //     cout<<"\n";
            // }
            return ans;
        }
};

int main() {
    //     vector<vector<int>> board = {
    //     {1, 2, 4, 3, 6},
    //     {2, 4, 6, 2, 3},
    //     {5, 4, 3, 1, 2},
    //     {1, 2, 5, 4, 6}
    // };
    
    // // Initialize FindPath with dimensions of the board and the board itself
    // FindPath fp(4, 5, board);
    srand(time(0)); // Seed for random number generation

    // Set the dimensions of the board
    int x = 1000; // Number of rows
    int y = 1000; // Number of columns

    // Generate a large board with random values between 1 and 10
    vector<vector<int>> board(x, vector<int>(y));

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            board[i][j] = rand() % 10 + 1; // Random number between 1 and 10
        }
    }

    // Initialize FindPath with dimensions of the board and the board itself
    FindPath fp(x, y, board);
    
    // Call naiveGraphFind to get the shortest path from the top to the bottom
    auto start_naive = high_resolution_clock::now(); // Start time
    int result = fp.naiveGraphFind();
    auto end_naive = high_resolution_clock::now(); // Start time
    auto duration_naive = duration_cast<milliseconds>(end_naive - start_naive);
    cout << "Time taken by naiveGraphSearch: " << duration_naive.count() << " ms" << endl;
    auto start_memo = high_resolution_clock::now(); // Start time
    int result2 = fp.dp_solution();
    auto end_memo = high_resolution_clock::now();   // End time
    auto duration_memo = duration_cast<milliseconds>(end_memo - start_memo);
    cout << "Time taken by memoMax: " << duration_memo.count() << " ms" << endl;
    // Print the result
    cout << "Shortest path weight: " << result << endl;
    cout << "Shortest path weight: " << result2 << endl;

    
    return 0;
}