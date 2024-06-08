#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <climits>
using namespace std;

class City{
public:
    unordered_map<int, vector<pair<int, int>>> edges;
};

int n, m;
City c;

vector<long long> dfs(int from, int src, int target1, int target2){
    stack<pair<int, long long>> stk;
    vector<long long> temp(2, LLONG_MAX);
    vector<int> visited(100000, false);
    stk.emplace(src, 0);

    while(!stk.empty()){
        auto cur = stk.top();
        stk.pop();
        if(visited[cur.first]) continue;
        visited[cur.first] = true;

        for(auto& it : c.edges[cur.first]){
            if(it.first == target1 && cur.second+it.second < temp[0]) temp[0] = cur.second+it.second;
            if(it.first == target2 && cur.second+it.second < temp[1]) temp[1] = cur.second+it.second; 
            
            stk.emplace(it.first, cur.second+it.second);
        }
    }

    return temp;
}

int main(){
    cin >> n >> m;

    while(m--){
        int from, to, weigh;
        cin >> from >> to >> weigh;

        c.edges[from].push_back(make_pair(to, weigh));
    }

    int op, tA, tB, dest;
    cin >> op;

    if(op == 1){
        cin >> tA >> dest;
        auto temp = dfs(-1, tA, dest, -1);
        cout << (temp[0]==LLONG_MAX ? -1 : temp[0]) << endl;
    }else if(op == 2){
        cin >> tA >> tB >> dest;
        auto temp1 = dfs(-1, tA, dest, tB);
        auto temp2 = dfs(-1, tB, dest, tA);

        if(temp1[0] == LLONG_MAX || temp2[0] == LLONG_MAX)
            cout << -1 << endl;
        else{
            auto abd = temp1[1]==LLONG_MAX ? LLONG_MAX : temp1[1]+temp2[0], 
                 bad = temp2[1]==LLONG_MAX ? LLONG_MAX : temp2[1]+temp1[0], 
                 adbd = temp1[0]+temp2[0];
            cout << min(abd, min(bad, adbd)) << endl;
        }
    }

    return 0;
}