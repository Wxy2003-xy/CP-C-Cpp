#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int dia1 = findDiameter(edges1);
        int dia2 = findDiameter(edges2);
        int a = ceil(dia1/2.0);
        int b = ceil(dia2/2.0);
        return max({dia1, dia2, (1 + a + b)});
    }
    void printAdj(vector<vector<int>> adj) {
        for (int i = 0; i < adj.size(); i++) {
            for (int j = 0; j < adj[i].size(); j++) {
                cout<<adj[i][j]<<"  ";
            }
            cout<<"\n";
        }
    }
    int findDiameter(vector<vector<int>>& edges) {
        if (edges.empty()) {
            return 0;
        }
        int len = edges.size() + 1;
        vector<vector<int>> adj = processAdj(edges, len); // process input to form adjacency list
        if (adj.empty() || (adj.size() == 1 && adj[0].empty())) {
            return 0;  // Single node or empty adjacency list
        }
        vector<bool> visited(len, false); // initialize visited array
        stack<pair<int, int>> s;
        s.push({0, 0});
        int depth = 0;
        int furthest = 0;
        while (!s.empty()) {
            pair<int, int> n = s.top();
            s.pop();
            int currNode = n.first;
            int currLevel = n.second;
            if (!visited[currNode]) {
                visited[currNode] = true;
                if (currLevel > depth) {
                    depth = currLevel;
                    furthest = currNode;
                }
                for (int i = 0; i < adj[currNode].size(); i++) {
                    s.push(make_pair(adj[currNode][i], currLevel + 1));
                }
            }
        }
        vector<bool> visited2(len, false);
        s.push({furthest, 0});
        int diameter = 0;
        while(!s.empty()) {
            pair<int, int> n = s.top();
            s.pop();
            int currNode = n.first;
            int currLevel = n.second;
            if (!visited2[currNode]) {
                visited2[currNode] = true;
                diameter = max(diameter, currLevel);
                if (adj[currNode].size() > 0) {
                    for (int i = 0; i < adj[currNode].size(); i++) {
                        s.push(make_pair(adj[currNode][i], currLevel + 1));
                    }
                }
            }
        }
        cout<<"dia "<< diameter;
        return diameter;
    }
    vector<vector<int>> processAdj(vector<vector<int>>& edges, int len) {
        vector<vector<int>> adj(len);
        if (len == 1) {
            return adj;
        }
        for (int i = 0; i < edges.size(); i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        return adj;
    }
};

int main() {
    Solution s;
    vector<vector<int>> e = {{0,1},{0,2},{0,3},{2,4},{2,5},{3,6},{2,7},{6,8}};
    vector<vector<int>> m = {{0, 1}};
    vector<vector<int>> l = {{0,1},{0,2},{0,3},{2,4},{2,5},{3,6},{2,7}};
    vector<vector<int>> p = {{0,1},{0,2},{0,3}};
    vector<vector<int>> w = {{0,1}};
    vector<vector<int>> a = {{0,1},{2,0},{3,2},{3,6},{8,7},{4,8},{5,4},{3,5},{3,9}};
    int x = s.minimumDiameterAfterMerge(p,a);

    cout<<x<<" ";
    return 0;
}