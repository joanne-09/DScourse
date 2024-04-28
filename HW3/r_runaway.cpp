#include <iostream>
#include <vector>
#define MAX(x, y) (x > y ? x : y)
using namespace std;

class TN{
public:
    int val, dist;
    long long max = -1e9, sec = -1e9;
    TN* parent = nullptr;
    vector<TN*> child;

    TN(int v, int d): val(v), dist(d){};
    void findDist(){
        max = sec = -1e9;
        if(child.empty()) return;

        long long temp;
        for(auto it : child){
            temp = MAX(it->dist + it->max, it->dist);
            if(temp > max){
                sec = max;
                max = temp;
            }else if(temp > sec){
                sec = temp;
            }
        }
    }
};

int n, o, v, d;
long long maxdist = -1e9, maxroot;
vector<TN*> tree(10005, nullptr);

void makeNode(int p, int c, int d){
    TN *parent = tree[p], *child = tree[c];
    if(!tree[p]){
        tree[p] = new TN(p, -1);
        parent = tree[p];
    }
    
    if(!tree[c]){
        tree[c] = new TN(c, d);
        child = tree[c];
    }else{
        tree[c]->dist = d;
    }

    child->parent = parent;
    parent->child.push_back(child);

    while(parent){
        parent->findDist();
        parent = parent->parent;
    }
}

void del(int b){
    if(!tree[b]) return;

    TN *forDel = tree[b], *parent = tree[b]->parent;
    auto it = parent->child.begin();
    for(; it != parent->child.end(); ++it){
        if(*it == forDel) break;
    }

    parent->child.erase(it);
    tree[b] = nullptr;

    for(auto it : forDel->child){
        it->parent = parent;
        parent->child.push_back(it);
    }

    while(parent){
        parent->findDist();
        parent = parent->parent;
    }

    delete forDel;
}

void check(){
    maxdist = -1e9;
    for(auto it : tree){
        if(!it) continue;
        long long temp = MAX(it->max + it->sec + it->dist, MAX(it->max + it->dist, it->dist));
        //cout << "root: " << it->val << " dist: " << temp << endl;
        if(temp > maxdist){
            maxdist = temp;
            maxroot = it->val;
        }
    }
}

int main(){
    cin >> n >> o >> v >> d;
    tree[v] = new TN(v, d);

    int pi, ci, di;
    while(n--){
        cin >> pi >> ci >> di;
        makeNode(pi, ci, di);
    }

    string op;
    while(o--){
        cin >> op;

        if(op == "Add"){
            cin >> pi >> ci >> di;
            makeNode(pi, ci, di);
        }else if(op == "Delete"){
            cin >> pi;
            del(pi);
        }else if(op == "Check"){
            check();
            cout << "Maximum Value: " << maxdist << endl;
            cout << "Root of the Path: " << maxroot << endl;
        }
    }

    check();
    cout << "Final Root: " << maxroot << endl;
    return 0;
}