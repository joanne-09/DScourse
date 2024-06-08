#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Graph{
    vector<vector<int>> edges;
    vector<vector<int>> labeled_edges;
    vector<vector<int>> select_edges;
    set<int> visited_vertices;
    int V;
public:
    Graph(int V) : V(V){}

    void AddEdge(int u, int v, int w){
        edges.push_back({w, u, v});
    }

    // find minimum spanning tree for undirected graph
    void Prim(){
        // start with vertex 0
        visited_vertices.insert(0);
    }
};

int main(){
    Graph g(4);
    g.AddEdge(0, 1, 10);
    g.AddEdge(0, 2, 6);
    g.AddEdge(0, 3, 5);
    g.AddEdge(1, 3, 15);
    g.AddEdge(2, 3, 4);

    return 0;
}