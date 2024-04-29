#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

class TN{
public:
    int val, dist;
    TN* parent = nullptr;
    vector<TN*> child;

    TN(int v, int d): val(v), dist(d){};
};

int n, o, v, d;
vector<TN*> tree(10005);
long long maxdist = INT_MIN;
TN *root = nullptr, *maxroot = nullptr;

void makeNode(int pi, int ci, int di){
    TN *parent = tree[pi], *child = tree[ci];
    if(!parent){
        tree[pi] = new TN(pi, -1);
        parent = tree[pi];
    }

    if(!child){
        tree[ci] = new TN(ci, di);
        child = tree[ci];
    }else
        tree[ci]->dist = di;

    child->parent = parent;
    parent->child.push_back(child);
}

void del(int pi){
    TN *forDel = tree[pi];
    if(!forDel) return;

    tree[pi] = nullptr;
    TN* parent = forDel->parent;

    auto it = find(parent->child.begin(), parent->child.end(), forDel);
    parent->child.erase(it);

    for(auto it : forDel->child){
        parent->child.push_back(it);
        it->parent = parent;
    }

    delete forDel;
}

long long dfs(TN* root){
    if(!root) return 0;

    long long maxval = 0, secval = 0;
    for(auto it : root->child){
        long long temp = dfs(it);
        if(temp > maxval){
            secval = maxval;
            maxval = temp;
        }else if(temp > secval){
            secval = temp;
        }
    }

    long long temp = maxval + secval + root->dist;
    if(temp > maxdist){
        maxdist = temp;
        maxroot = root;
    }

    return maxval + root->dist;
}

void check(){
    maxdist = INT_MIN;
    dfs(root);
    cout << "Maximum Value: " << maxdist << endl;
    cout << "Root of the Path: " << maxroot->val << endl;
}

void final(){
    maxdist = INT_MIN;
    dfs(root);
    cout << "Final Root: " << maxroot->val << endl;
}

int main(){
    cin >> n >> o >> v >> d;
    tree[v] = new TN(v, d);
    root = tree[v];

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
        }
    }

    final();
}