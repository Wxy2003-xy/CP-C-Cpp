#include<bits/stdc++.h>
using namespace std;

void topological_sort(vector<vector<pair<int, int>>> edges, vector<bool>& visited,
                    stack<int>& s, vector<int>& dist, int start) {
    visited[start] = true;
    for (int i = 0; i < edges[start].size(); i++) {
        visited[edges[start][i].first] = true;
        dist[edges[start][i].first] = max(dist[edges[start][i].first],
                                        dist[start] + edges[start][i].second);
        s.push(edges[start][i].first);
        topological_sort(edges, visited, s, dist, edges[start][i].first);
    }
}

void min_topological_sort(vector<vector<pair<int, int>>> edges, vector<bool>& visited,
                    stack<int>& s, vector<int>& dist, int start) {
    visited[start] = true;
    for (int i = 0; i < edges[start].size(); i++) {
            visited[edges[start][i].first] = true;
            dist[edges[start][i].first] = min(dist[edges[start][i].first],
                                            dist[start] + edges[start][i].second);
            s.push(edges[start][i].first);
            min_topological_sort(edges, visited, s, dist, edges[start][i].first);
    }
}


int main() {
    vector<vector<pair<int, int>>> edges(10);
    vector<bool> visited(10, false);
    stack<int> s;
    vector<int> dist(10, 0); 
    vector<int> dist_min(10, INT_MAX); 
    dist_min[0] = 0;

    edges[0].push_back({1, 4});
    edges[0].push_back({2, 3});
    edges[1].push_back({3, 6});
    edges[1].push_back({4, 2});
    edges[2].push_back({4, 7});
    edges[2].push_back({5, 5});
    edges[3].push_back({6, 1});
    edges[4].push_back({6, 3});
    edges[5].push_back({7, 8});
    edges[6].push_back({8, 2});
    edges[7].push_back({9, 6});
    edges[8].push_back({9, 4});

    // Perform topological sort starting from node 0
    s.push(0);
    min_topological_sort(edges, visited, s, dist_min, 0);

    // Output the result
    cout << "Topologically sorted order: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    // Output the distances (longest path in DAG from node 0)
    cout << "Distances from start node (0): ";
    for (int i = 0; i < dist.size(); i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
/*

*/
    return 0;
}