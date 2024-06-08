#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Graph{
    vector<vector<int>> edges;
    vector<vector<int>> select_edges;
    set<int> visited_vertices;
    int V;
public:
    Graph(int V) : V(V){}

    void AddEdge(int u, int v, int w){
        edges.push_back({w, u, v});
    }

    // find minimum spanning tree for undirected graph
    void Kruskal(){
        sort(edges.begin(), edges.end(), [&](vector<int>& a, vector<int>& b){
            return a[0] < b[0];
        });

        for(int i=0; i<V-1; ++i){
            while(1){
                auto candidate = *edges.begin();
                edges.erase(edges.begin());

                auto it1 = visited_vertices.find(candidate[1]);
                auto it2 = visited_vertices.find(candidate[2]);

                if(!visited_vertices.empty() && it1 != visited_vertices.end() && it2 != visited_vertices.end())
                    continue;
                
                select_edges.push_back(candidate);
                visited_vertices.insert(candidate[1]);
                visited_vertices.insert(candidate[2]);
                break;
            }
        }

        for(auto& it : select_edges){
            cout << it[1] << " - " << it[2] << " : " << it[0] << endl;
        }
    }
};

int main(){
    Graph g(4);
    g.AddEdge(0, 1, 10);
    g.AddEdge(0, 2, 6);
    g.AddEdge(0, 3, 5);
    g.AddEdge(1, 3, 15);
    g.AddEdge(2, 3, 4);

    g.Kruskal();

    return 0;
}