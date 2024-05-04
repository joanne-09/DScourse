#include <iostream>
#include <vector>
using namespace std;

class Edge{
public:
    int src, dest, dist, traffic;

    Edge(int s, int d, int dis, int t): src(s), dest(d), dist(dis), traffic(t){};

};

class Vertex{
public:
    int id, dman;
    vector<Edge*> road;

    Vertex(int v, int c): id(v), dman(c){};
};

class Map{
public:
    vector<Vertex*> vertex;
    vector<Edge*> edges;

    Map(int size){
        vertex.resize(size+1, nullptr);
        for(int i=1; i<=size; ++i){
            vertex[i] = new Vertex(i, -1);
        }
    }

    void placeDman(int v, int c){
        vertex[v]->dman = c;
    }

    void addEdge(int s, int d, int dis, int t){
        Edge* newedge = new Edge(s, d, dis, t);
        vertex[s]->road.push_back(newedge);
        vertex[d]->road.push_back(newedge);
        edges.push_back(newedge);
    }
};

int V, E, D, C;
int v, c, s, d, dis, t;
string op;

Map map;

void initialMap(){
    map = Map(V);
    while(D--){
        cin >> op >> v >> c;
        map.placeDman(v, c);
    }
    while(E--){
        cin >> op >> s >> d >> dis >> t;
        map.addEdge(s, d, dis, t);
    }
}

void order(){
    int id, src, ts;
    cin >> id >> src >> ts;
}

void drop(){
    int id, dst;
    cin >> id >> dst;
}

void complete(){
    int id;
    cin >> id;
}

int main(){
    cin >> V >> E >> D;

    initialMap();

    cin >> C;
    while(C--){
        cin >> op;
        if(op == "Order"){
            order();
        }else if(op == "Drop"){
            drop();
        }else if(op == "Complete"){
            complete();
        }
    }
    return 0;
}