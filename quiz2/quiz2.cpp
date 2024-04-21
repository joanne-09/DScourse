#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

int n, x;

class Pokemon{
public:
    int id, lvl = 1;
    Pokemon(int id, int lvl): id(id), lvl(lvl) {};
};

vector<list<Pokemon*>> pokes;

void insert(){
    int listidx, idx, lvl;
    cin >> listidx >> idx >> lvl;

    Pokemon* pokemon = new Pokemon(idx, lvl);
    pokes[listidx].push_back(pokemon);
}

void remove(){
    int listidx, idx;
    cin >> listidx >> idx;

    auto it = pokes[listidx].begin();

    for(; it != pokes[listidx].end(); ){
        if((*it)->id == idx){
            it = pokes[listidx].erase(it);
        }else ++it;
    }
}

void rotate(){
    int listidx, cnt;
    cin >> listidx >> cnt;

    cnt %= pokes[listidx].size();

    while(cnt--){
        auto temp = pokes[listidx].back();
        pokes[listidx].pop_back();
        pokes[listidx].push_front(temp);
    }
}

void reorder(){
    int listidx, cnt = 0;
    cin >> listidx;

    int size = pokes[listidx].size();
    auto it = pokes[listidx].begin();

    for(; cnt < size; cnt++){
        if(cnt % 2 == 1){
            auto temp = *it;
            it = pokes[listidx].erase(it);
            pokes[listidx].push_back(temp);
        }else ++it;
    }
}

void myreverse(){
    int listidx, start, end;
    cin >> listidx >> start >> end;
    end = min(end, (int)pokes[listidx].size());
    auto it = pokes[listidx].begin(), l = next(it, start), r = next(it, end);
    reverse(l, ++r);
}

void merge(){
    int idx1, idx2;
    cin >> idx1 >> idx2;
    list<Pokemon*> ll;

    auto it = pokes[idx1].begin();
    auto itr = pokes[idx2].begin();

    while(it != pokes[idx1].end() || itr != pokes[idx2].end()){
        if(it == pokes[idx1].end()){
            ll.push_back(*itr);
            ++itr;
        }else if(itr == pokes[idx2].end()){
            ll.push_back(*it);
            ++it;
        }else if((*it)->lvl < (*itr)->lvl){
            ll.push_back(*it);
            ++it;
        }else if((*it)->lvl == (*itr)->lvl && (*it)->id < (*itr)->id){
            ll.push_back(*it);
            ++it;
        }else{
            ll.push_back(*itr);
            ++itr;
        }
    }

    pokes[idx2].clear(), pokes[idx1].clear();
    pokes[idx1].splice(pokes[idx1].begin(), ll);
}

void show(int i){
    cout << "List " << i << endl;
    if(!pokes[i].empty()){
        for(auto it : pokes[i]){
            cout << "ID: " << it->id << " Level: " << it->lvl << endl;
        }
    }else{
        cout << "Empty\n";
    }
}

int main(){
    cin >> n >> x;
    pokes.resize(n);

    string op;
    while(x--){
        cin >> op;
        if(op == "Insert"){
            insert();
        }else if(op == "Reverse"){
            myreverse();
        }else if(op == "Rotate"){
            rotate();
        }else if(op == "Reorder"){
            reorder();
        }else if(op == "MergeListsPreserveOrder"){
            merge();
        }else if(op == "Remove"){
            remove();
        }else if(op == "Show"){
            show(0);
        }
    }

    for(int i=0; i<n; ++i) show(i);
    return 0;
}