#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int maxLength = -1;
        void getcycle(vector<int> &edges,int start,
                    vector<bool>& visit,vector<int>& store){
            if(start == -1)return ; // if prev node leads to nowhere, current node is a sink
            if(visit[start]){ // if the node is already visited
                int count = -1; 
                for(int i =0;i<store.size();i++){
                    if(store[i]==start){ // if current node has been recorded
                        count = i; // set count to be the index of start in store
                        break;
                    }
                }
                if(count==-1)return; // if current node is not found in a path 
                                     // -> no cycle in current component
                int size = (store.size()-count); 
                maxLength = max(maxLength,size); // update current max cycle length
                return ;
            }
            visit[start] = true; // mark this node as visited
            store.push_back(start); // mark this node as appeared in current path
            getcycle(edges,edges[start],visit,store); // edges[start] -> start.next
            return ; // finish exploring a component
        }
        int longestCycle(vector<int>& edges) { 
            vector<bool> visit(edges.size(),0);
            for(int i =0;i<edges.size();i++){
                if(visit[i])continue; // node i is in an already explored component
                vector<int> store;
                getcycle(edges,i,visit,store); // find the cycle length 
                                               // (if existent) in the component containing i
            }
            return maxLength;
        }
};

int main() {

}