#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <climits>
using namespace std;

class Vertex{
public:
    int id, dman;
    Vertex(int i, int man): id(i), dman(man){}
};

class Edge{
public:
    int src, dest, dist, traffic;
    Edge(int s, int d, int dis, int t):src(s), dest(d), dist(dis), traffic(t){}
};

class Order{
public:
    int id, src, dst, ts;
    int minpath = INT_MAX;
    bool pending = false;
    vector<pair<int, int>> path;
    Order(int i, int s, int t): id(i), src(s), dst(0), ts(t){}
};

class Map{
public:
    int size, pend = 0;
    vector<Vertex*> vertex;
    vector<vector<Edge*>> edges;
    vector<Order*> order;

    Map(): size(105){}
    Map(int v): size(v){
        vertex.resize(size+1, nullptr);
        edges.resize(size+1);
        order.resize(105, nullptr);
        for(int i=1; i<=size; ++i){
            vertex[i] = new Vertex(i, 0);
            edges[i].resize(size+1, nullptr);
        }
    }

    Vertex* operator[](int idx){
        return vertex[idx];
    }

    Edge* operator()(int s, int d){
        return edges[s][d];
    }

    void reserve(vector<pair<int, int>> path, int ts){
        for(auto it : path){
            //cout << it.first << " " << it.second << endl;
            edges[it.first][it.second]->traffic -= ts;
        }
    }

    void undoreserve(vector<pair<int, int>> path, int ts){
        for(auto it : path){
            //cout << it.first << " " << it.second << endl;
            edges[it.first][it.second]->traffic += ts;
        }
    }
};

class Algo{
public:
    int size;
    int driver = 0;
    vector<bool> visited;
    vector<int> dist;
    vector<pair<int, int>> path;

    Algo(int s, int src): size(s){
        visited.resize(size+1, false);
        dist.resize(size+1, INT_MAX);
        path.resize(size+1);
        path.clear();
        visited[src] = true;
        dist[src] = 0;
        path[src] = make_pair(0, 0);
    }

    int minpath(int src, int target, int ts, Map& map){
        if(src == 0) return INT_MAX;
        if(src == target) return dist[src];
        if(map[src]->dman > 0 && dist[src] < dist[driver]){
            driver = src;
        }

        visited[src] = true;
        for(int i=1; i<=size; ++i){
            if(!map(src, i)) continue;
            if(map(src, i)->traffic < ts) continue;

            int temp = dist[src] + map(src, i)->dist;
            if(temp < dist[i]){
                dist[i] = temp;
                path[i] = make_pair(src, i);
            }

            if(map[i]->dman > 0 && dist[i] < dist[driver]){
                driver = i;
            }
        }

        int next = nextvisit();
        return minpath(next, target, ts, map);
    }

    int nextvisit(){
        int mindist = INT_MAX;
        int ret = 0;
        for(int i=1; i<=size; ++i){
            if(visited[i]) continue;
            if(dist[i] < mindist){
                mindist = dist[i];
                ret = i;
            }
        }

        return ret;
    }

    vector<pair<int, int>> retpath(int src){
        int cur = src;
        vector<pair<int, int>> ret;
        while(path[cur].first != 0){
            ret.push_back(path[cur]);
            cur = path[cur].first;
        }
        return ret;
    }
};

int V, E, D, C;
int v, c, s, d, dis, t;
string op;
Map map;

void initmap(){
    cin >> V >> E >> D;
    map = Map(V);
    while(D--){
        cin >> op >> v >> c;
        map[v]->dman = c;
    }

    while(E--){
        cin >> op >> s >> d >> dis >> t;
        Edge* newedge = new Edge(s, d, dis, t);
        map.edges[s][d] = map.edges[d][s] = newedge;
    }
}

void order(){
    int id, src, ts;
    cin >> id >> src >> ts;
    map.order[id] = new Order(id, src, ts);
    Algo algo(map.size, src);

    algo.minpath(src, 0, ts, map);
    if(algo.driver != 0){
        map.order[id]->path = algo.retpath(algo.driver);
        map.order[id]->minpath = algo.dist[algo.driver];
        cout << "Order " << id << " from: " << algo.driver << endl;
        map.reserve(map.order[id]->path, ts);
        map[algo.driver]->dman--;
    }else{
        cout << "Just walk. T-T\n";
        delete map.order[id];
    }
}

bool deliver(int id){
    Algo algo(map.size, map.order[id]->src);
    int temp = algo.minpath(map.order[id]->src, map.order[id]->dst, map.order[id]->ts, map);

    if(temp == INT_MAX) return false;
    else{
        map.order[id]->path = algo.retpath(map.order[id]->dst);
        map.order[id]->minpath += temp;
        cout << "Order " << id << " distance: " << map.order[id]->minpath << endl;
        map.reserve(map.order[id]->path, map.order[id]->ts);
        return true;
    }
}

void drop(){
    int id, dst;
    cin >> id >> dst;
    map.order[id]->dst = dst;
    map.undoreserve(map.order[id]->path, map.order[id]->ts);

    if(!deliver(id)){
        cout << "No Way Home\n";
        map.pend++;
        map.order[id]->pending = true;
    }
}

void complete(){
    int id;
    cin >> id;
    map.undoreserve(map.order[id]->path, map.order[id]->ts);
    map[map.order[id]->dst]->dman ++;

    if(map.pend == 0) return;
    for(int i=1; i<=100; ++i){
        if(!map.order[i]) continue;
        if(!map.order[i]->pending) continue;
        if(deliver(i)){
            map.order[i]->pending = false;
            map.pend--;
        }
    }
}

int main(){
    initmap();
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