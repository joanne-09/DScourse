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

    Vertex* smallestdist(){
        int mindist = INT_MAX;
        Vertex* ret = nullptr;
        for(auto it : dist){
            if(it.first->dman <= 0) continue;

            if(mindist > it.second){
                mindist = it.second;
                ret = it.first;
            }else if(ret){
                if(mindist == it.second && path[ret].size() > path[it.first].size()){
                    mindist = it.second;
                    ret = it.first;
                }else if(mindist == it.second && path[ret].size() == path[it.first].size() && ret->id > it.first->id){
                    mindist = it.second;
                    ret = it.first;
                }
            }
        }

        return ret;
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

    map.order[id] = new Order(map[src], ts, id);
    Order* order = map.order[id];

    Algo algo(map.size, map, map[src]);
    algo.minpath(order->src, nullptr, order->ts, map);
    Vertex* DL = algo.smallestdist();
    
    if(DL){
        order->updateOrder(algo.path[DL], DL, algo.dist[DL]);
        cout << "Order " << id << " from: " << DL->id << endl;
        order->driver->dman--;
        map.updateMap(order->path, ts);
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