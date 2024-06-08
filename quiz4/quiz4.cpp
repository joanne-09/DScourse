#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <climits>
using namespace std;

class Map{
public:
    int size;
    vector<vector<pair<int, int>>> stops;
    Map(){size = 105;}
    Map(int s): size(s){
        stops.resize(s+1);
    }
};

Map map;
class Algo{
public:
    int size, src;
    vector<bool> visited;
    vector<long long> dist;

    Algo(int s, int src1): size(s), src(src1){
        visited.resize(s+1, false);
        dist.resize(s+1, INT_MAX);
        dist[src] = 0;
    }

    long long minpath(int src, int target){
        if(src == -1) return -1;
        
        visited[src] = true;
        for(auto it : map.stops[src]){
            if(visited[it.first]) continue;
            long long temp = dist[src] + it.second;
            if(temp < dist[it.first]){
                dist[it.first] = temp;
            }
        }

        int next = nextvisit();
        return minpath(next, target);
    }

    int nextvisit(){
        int next = -1;
        long long min = INT_MAX;

        for(int i=0; i<size; ++i){
            if(visited[i]) continue;
            if(dist[i] < min){
                min = dist[i];
                next = i;
            }
        }

        return next;
    }
};

int n, m, t, a, b, dest;
int from, to, w;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    map = Map(n);
    while (m--){
        cin >> from >> to >> w;
        map.stops[from].emplace_back(to, w);
    }

    cin >> t;
    if(t == 1){
        cin >> a >> dest;
        Algo algo(map.size, a);
        algo.minpath(a, dest);
        long long temp = algo.dist[dest];
        cout << temp << endl;
    }else if(t == 2){
        cin >> a >> b >> dest;
        Algo algo1(map.size, a);
        Algo algo2(map.size, b);
        algo1.minpath(a, dest);
        algo2.minpath(b, dest);

        long long temp1 = algo1.dist[dest], temp3 = algo1.dist[b];
        long long temp2 = algo2.dist[dest], temp4 = algo2.dist[a];

        if(temp1 == -1 || temp2 == -1){
            cout << -1 << endl;
            return 0;
        }

        long long temp = temp1 + temp2;
        if(temp3 != INT_MAX && temp2 + temp3 < temp){
            temp = temp2 + temp3;
        }
        if(temp4 != INT_MAX && temp4 + temp1 < temp){
            temp = temp4 + temp1;
        }
        cout << temp << endl;
    }
    return 0;
}