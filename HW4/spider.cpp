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
    Vertex *driver, *src, *dst;
    int ts, minpath, id;

    Order(Vertex* s, int t, int i): src(s), ts(t), id(i){
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
    vector<Order*> pending;

    Map():size(0){};
    Map(int s): size(s){
        vertex.resize(size+1, nullptr);
        for(int i=1; i<=size; ++i){
            vertex[i] = new Vertex(i, 0);
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

    void updateMap(vector<Edge*> path, int ts){
        for(auto it : path){
            it->trafficnow += ts;
        }
    }

    void reverseMap(vector<Edge*> path, int ts){
        for(auto it : path)
            it->trafficnow -= ts;
    }

    void sortpending(){
        int size = pending.size();
        for(int i=0; i<size; ++i){
            for(int j=i+1; j<size; ++j){
                if(pending[j]->id < pending[i]->id){
                    Order* temp = pending[j];
                    pending[j] = pending[i];
                    pending[i] = temp;
                }
            }
        }
    }
};

class Algo{
public:
    int size;
    unordered_map<Vertex*, bool> visited;
    unordered_map<Vertex*, int> dist;
    unordered_map<Vertex*, vector<Edge*>> path;
    Algo(int s, Map& m, Vertex* src): size(s){
        for(int i=1; i<=size; i++){
            visited[m[i]] = false;
            dist[m[i]] = INT_MAX;
        }
        dist[src] = 0;
    }

    int minpath(Vertex* src, Vertex* target, int ts, Map& map){
        if(src == nullptr) return INT_MAX;
        if(src == target) return dist[target];

        visited[src] = true;
        for(auto it : src->road){
            Vertex* visit = map[it.first];
            Edge* road = it.second;

            if(road->traffic < road->trafficnow + ts) continue;

            int temp = dist[src] + road->dist;
            if(temp < dist[visit] || (temp == dist[visit] && path[src].size() +1 < path[visit].size())){
                dist[visit] = temp;
                path[visit] = path[src];
                path[visit].push_back(road);
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
unordered_map<Vertex*, bool> visited;
Vertex* driverfrom;
int mintemp = INT_MAX;
void mindist(Vertex* src, Vertex* from, int dist, int ts, vector<Edge*> temppath){
    visited[src] = true;
    if(src->dman > 0){
        if(dist < mintemp || (dist == mintemp && temppath.size() < minpath.size()) || (dist == mintemp && temppath.size() == minpath.size() && src->id < driverfrom->id)){
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
        if(visited[toward]) continue;
        if(road->traffic < road->trafficnow + ts) continue;

        temppath.push_back(road);
        mindist(toward, src, dist + road->dist, ts, temppath);
        temppath.pop_back();
    }
}

void order(){
    int id, src, ts;
    cin >> id >> src >> ts;

    map.order[id] = new Order(map[src], ts, id);
    vector<Edge*> vect;
    vect.clear();
    visited.clear();

    mintemp = INT_MAX;
    mindist(map[src], nullptr, 0, ts, vect);
    
    if(mintemp != INT_MAX){
        map.order[id]->updateOrder(minpath, driverfrom, mintemp);
        cout << "Order " << id << " from: " << driverfrom->id << endl;
        driverfrom->dman--;
        map.updateMap(minpath, ts);
    }else{
        cout << "Just walk. T-T\n";
        delete map.order[id];
    }
}

bool drop(Order* order){
    map.reverseMap(order->path, order->ts);

    Algo algo(map.size, map, order->src);
    int path = algo.minpath(order->src, order->dst, order->ts, map);
    if(path == INT_MAX) return false;
    else{
        cout << "Order " << order->id << " distance: " << path + order->minpath << endl;
        order->path = algo.path[order->dst];
        map.updateMap(order->path, order->ts);
        return true;
    }
}

void placeorder(){
    int id, dst;
    cin >> id >> dst;

    map.order[id]->dst = map[dst];
    if(!drop(map.order[id])){
        cout << "No Way Home\n";
        map.pending.push_back(map.order[id]);
    }
}

void complete(){
    int id;
    cin >> id;
    Order* order = map.order[id];
    map.reverseMap(order->path, order->ts);
    order->dst->dman++;

    delete order;
    if(map.pending.empty()) return;

    map.sortpending();
    for(auto it = map.pending.begin(); it != map.pending.end(); ){
        if(drop(*it)){
            it = map.pending.erase(it);
        }else ++it;
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