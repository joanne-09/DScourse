#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

class Edge{
public:
    int src, dest, dist, traffic, trafficnow = 0;

    Edge(int s, int d, int dis, int t): src(s), dest(d), dist(dis), traffic(t){};

};

class Vertex{
public:
    int id, dman;
    unordered_map<int, Edge*> road;

    Vertex(int v, int c): id(v), dman(c){};
};

class Order{
public:
    vector<Edge*> path;
    Vertex *driver, *src;
    int ts, minpath;

    Order(Vertex* s, int t): src(s), ts(t){
        minpath = INT_MAX;
        path.clear();
    }

    void updateOrder(vector<Edge*> p, Vertex* d, int pa){
        path = p;
        driver = d;
        minpath = pa;
    }
};

class Map{
public:
    int size;
    vector<Vertex*> vertex;
    vector<Edge*> edges;
    unordered_map<int, Order*> order;

    Map():size(0){};
    Map(int s): size(s){
        vertex.resize(size+1, nullptr);
        for(int i=1; i<=size; ++i){
            vertex[i] = new Vertex(i, -1);
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
        vertex[s]->road[d] = newedge;
        vertex[d]->road[s] = newedge;
        edges.push_back(newedge);
    }

    void updateMap(vector<Edge*> path, int ts, Vertex* origin){
        origin->dman--;
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
    unordered_map<Vertex*, bool> visited;
    unordered_map<Vertex*, int> dist;
    Algo(int s, Map& m, Vertex* src): size(s){
        for(int i=1; i<=size; i++){
            visited[m[i]] = false;
            dist[m[i]] = INT_MAX;
        }
        dist[src] = 0;
    }

    int minpath(Vertex* src, Vertex* target, int ts, Map& map){
        if(src == target) return dist[target];

        visited[src] = true;
        for(auto it : src->road){
            Vertex* visit = map[it.first];
            Edge* road = it.second;

            if(road->traffic < road->trafficnow + ts) continue;

            int temp = dist[src] + road->dist;
            if(temp < dist[visit]){
                dist[visit] = temp;
            }
        }

        Vertex* next = nextvisit(map);
        return minpath(next, target, ts, map);
    }

    Vertex* nextvisit(Map& map){
        int path = INT_MAX;
        Vertex* next;

        for(int i=1; i<=size; ++i){
            if(visited[map[i]]) continue;
            
            if(path > dist[map[i]]){
                path = dist[map[i]];
                next = map[i];
            }            
        }
        return next;
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

vector<Edge*> minpath;
Vertex* driverfrom;
int mintemp = INT_MAX;
void mindist(Vertex* src, Vertex* from, int dist, int ts, vector<Edge*> temppath){
    if(src->dman > 0){
        if(dist < mintemp || (dist == mintemp && temppath.size() < minpath.size())){
            mintemp = dist;
            minpath = temppath;
            driverfrom = src;
        }
        return;
    }

    for(auto it : src->road){
        Vertex* toward = map[it.first];
        Edge* road = it.second;
        int temp;
        if(toward == from) continue;
        if(road->traffic < road->trafficnow + ts) continue;

        temppath.push_back(road);
        mindist(toward, src, ts, dist + road->dist, temppath);
        temppath.pop_back();
    }
}

void order(){
    int id, src, ts;
    cin >> id >> src >> ts;

    map.order[id] = new Order(map[src], ts);
    vector<Edge*> vect;

    mintemp = INT_MAX;
    mindist(map[src], nullptr, 0, ts, vect);
    
    if(mintemp != INT_MAX){
        map.order[id]->updateOrder(minpath, driverfrom, mintemp);
        cout << "Order " << id << " from: " << driverfrom->id << endl;
        map.updateMap(minpath, ts, driverfrom);
    }else{
        cout << "Just walk. T-T\n";
    }
}

void drop(){
    int id, dst;
    cin >> id >> dst;

    Order* order = map.order[id];
    map.reverseMap(order->path, order->ts);

    Algo algo(map.size, map, order->src);
    int path = algo.minpath(order->src, map[dst], order->ts, map);
    cout << path << endl << order->minpath << endl;
    cout << "Order " << id << " distance: " << path + order->minpath << endl;
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