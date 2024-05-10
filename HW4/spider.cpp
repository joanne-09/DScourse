#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

class Edge{
public:
    int src, dest, dist, traffic, trafficnow = 0;

    Edge(int s, int d, int dis, int t): src(s), dest(d), dist(dis), traffic(t), trafficnow(0){};

};

class Vertex{
public:
    int id, dman;

    Vertex(int v, int c): id(v), dman(c){};
};

class Order{
public:
    vector<Edge*> path;
    Vertex *src, *dst;
    int ts, minpath, id;

    Order(Vertex* s, int t, int i): src(s), ts(t), id(i){
        minpath = INT_MAX;
        path.clear();
    }

    void updateOrder(vector<Edge*> p, int pa){
        path = p;
        minpath = pa;
    }
};

class Map{
public:
    int size, edge, pend = 0;
    vector<Vertex*> vertex;
    vector<vector<Edge*>> edges;
    unordered_map<int, Order*> order;
    vector<bool> pending;

    Map():size(105){};
    Map(int s, int e): size(s), edge(e){
        vertex.resize(size+5, nullptr);
        edges.resize(size+5);
        pending.resize(105, false);
        for(int i=1; i<=size; ++i){
            vertex[i] = new Vertex(i, 0);
            edges[i].resize(size+5, nullptr);
        }
    }

    Vertex* operator[](int x){
        return vertex[x];
    }

    void placeDman(int v, int c){
        vertex[v]->dman = c;
    }

    void addEdge(int s, int d, int dis, int t){
        Edge* newedge = new Edge(s, d, dis, t);
        edges[s][d] = edges[d][s] = newedge;
    }

    void updateMap(vector<Edge*> path, int ts){
        for(auto it : path){
            it->trafficnow += ts;
        }
    }

    void reverseMap(vector<Edge*> path, int ts){
        for(auto it : path)
            it->trafficnow -= ts;
    }
};

class Algo{
public:
    int size;
    Vertex* candidate;
    vector<Edge*> cpath;
    unordered_map<Vertex*, bool> visited;
    unordered_map<Vertex*, int> dist;
    unordered_map<Vertex*, vector<Edge*>> path;

    void init(int s, Map& m, Vertex* src){
        size = s;
        for(int i=1; i<=size; i++){
            visited[m[i]] = false;
            dist[m[i]] = INT_MAX;
        }
        dist[src] = 0;
        path[src].clear();
        if(src->dman > 0) candidate = src;
        else candidate = nullptr;
        cpath.clear();
    }

    int minpath(Vertex* src, Vertex* target, int ts, Map& map){
        if(src == nullptr) return INT_MAX;
        if(src == target) return dist[target];

        visited[src] = true;
        for(int i=1; i<=size; ++i){
            if(!map.edges[src->id][i]) continue;
            Vertex* visit = map[i];
            Edge* road = map.edges[src->id][i];

            if(road->traffic < road->trafficnow + ts) continue;

            int temp = dist[src] + road->dist;
            if(temp < dist[visit]){
                dist[visit] = temp;
                path[visit] = path[src];
                path[visit].push_back(road);
            }

            if(visit->dman > 0){
                if(!candidate || dist[candidate] > dist[visit]){
                    candidate = visit;
                    cpath = path[candidate];
                }
            }
        }

        Vertex* next = nextvisit(map);
        return minpath(next, target, ts, map);
    }

    Vertex* nextvisit(Map& map){
        int path = INT_MAX;
        Vertex* next = nullptr;

        for(int i=1; i<=size; ++i){
            if(visited[map[i]]) continue;
            
            if(path > dist[map[i]]){
                path = dist[map[i]];
                next = map[i];
            }            
        }
        return next;
    }

    void check(Map& map){
        for(int i=1; i<=size; ++i){
            cout << "vertex " << i << " :" << endl;
            cout << "  distance: " << dist[map[i]] << endl;
            cout << "  path: ";
            for(auto it : path[map[i]]){
                cout << it->src << "->" << it->dest << "  ";
            }
            cout << endl;
        }
        cout << endl;

        if(candidate){
            cout << candidate->id << ": " << dist[candidate] << endl;
            for(auto it : cpath){
                cout << it->src << " " << it->dest << endl;
            }
        }   
    }
};

int V, E, D, C;
int v, c, s, d, dis, t;
string op;

Map map;
Algo algo;
void initialMap(){
    map = Map(V, E);
    while(D--){
        cin >> op >> v >> c;
        if(op == "PLACE") map.placeDman(v, c);
    }
    while(E--){
        cin >> op >> s >> d >> dis >> t;
        if(op == "EDGE") map.addEdge(s, d, dis, t);
    }
}

void order(){
    int id, src, ts;
    cin >> id >> src >> ts;

    map.order[id] = new Order(map[src], ts, id);

    algo.init(map.size, map, map[src]);
    algo.minpath(map.order[id]->src, nullptr, map.order[id]->ts, map);
    
    if(algo.candidate){
        algo.cpath = algo.path[algo.candidate];
        map.order[id]->updateOrder(algo.cpath, algo.dist[algo.candidate]);
        cout << "Order " << id << " from: " << algo.candidate->id << endl;
        algo.candidate->dman--;
        map.updateMap(map.order[id]->path, ts);
    }else{
        cout << "Just walk. T-T\n";
        //delete map.order[id];
    }
}

bool drop(int id){
    algo.init(map.size, map, map.order[id]->src);
    int path = algo.minpath(map.order[id]->src, map.order[id]->dst, map.order[id]->ts, map);
    if(path == INT_MAX) return false;
    else{
        cout << "Order " << map.order[id]->id << " distance: " << path + map.order[id]->minpath << endl;
        map.order[id]->path = algo.path[map.order[id]->dst];
        map.updateMap(map.order[id]->path, map.order[id]->ts);
        return true;
    }
}

void placeorder(){
    int id, dst;
    cin >> id >> dst;

    map.order[id]->dst = map[dst];
    map.reverseMap(map.order[id]->path, map.order[id]->ts);
    if(!drop(id)){
        cout << "No Way Home\n";
        map.pending[id] = true;
        map.pend++;
    }
}

void complete(){
    int id;
    cin >> id;
    Order* order = map.order[id];
    map.reverseMap(order->path, order->ts);
    order->dst->dman++;

    //delete order;
    if(map.pend == 0) return;

    for(int i=0; i<=100; ++i){
        if(!map.pending[i]) continue;
        if(drop(i)){
            map.pending[i] = false;
            map.pend--;
        }
    }
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
            placeorder();
        }else if(op == "Complete"){
            complete();
        }
    }
    return 0;
}