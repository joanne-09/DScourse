#include <iostream>
#include <climits>
#include <string>
#include <vector>
#define MAX(x, y) (x>y ? x : y)
using namespace std;

class TN{
public:
    int val, distance;
    long long max = LLONG_MIN, sec = LLONG_MIN;
    TN* parent = nullptr;
    vector<TN*> child;

    TN(int val, int dist): val(val), distance(dist) {};
    void modify(long long value){
        if(value > max){
            sec = max;
            max = value;
        }else if(value > sec && value != max)
            sec = value;
    }

    void finddist(){
        if(child.empty()) return;

        max = sec = LLONG_MIN;
        for(auto it : child){
            if(it->max == LLONG_MIN || it->sec == LLONG_MIN){
                if(it->child.empty()){
                    modify(it->distance);
                }else
                    it->finddist();
            }else{
                long long temp1 = it->max + it->distance;
                long long temp2 = it->sec + it->distance;
                modify(temp1);
                if(max != temp1 && sec != temp1) 
                    modify(temp2);
            }
        }

        //cout << max << " " << sec << endl;
    }
};

int n, o, v, d;
long long path = LLONG_MIN;
TN *rootPath = nullptr;
vector<TN*> tree;
TN* root = nullptr;

TN* makeNode(int pi, int ci, int di){
    TN *parent = nullptr, *target = nullptr;
    int parflag = 0;

    for(int i=0; i<tree.size(); i++){
        if(tree[i]->val == pi) parent = tree[i];
        if(tree[i]->val == ci) target = tree[i];
    }

    if(!parent){
        parent = new TN(pi, -1);
        tree.push_back(parent);
        parflag = 1;
    }

    if(!target){
        target = new TN(ci, di);
        tree.push_back(target);
    }else{
        target->distance = di;
    }

    target->parent = parent;
    parent->child.push_back(target);
    
    target->finddist();
    if(!parflag) parent->finddist();
}

void deleteNode(int node){
    TN *forDel = nullptr, *parent = nullptr;
    int treeidx = 0, childidx = 0;
    for(; treeidx<tree.size(); treeidx++){
        if(tree[treeidx]->val == node){
            forDel = tree[treeidx];
            break;
        }
    }

    if(!forDel) return;
    parent = forDel->parent;
    
    for(int i=0; i<forDel->child.size(); i++){
        forDel->child[i]->parent = parent;
        parent->child.push_back(forDel->child[i]);
    }

    for(; childidx<parent->child.size(); childidx++){
        if(parent->child[childidx]->val == forDel->val) break;
    }
    
    tree.erase(next(tree.begin(), treeidx));
    parent->child.erase(next(parent->child.begin(), childidx));
    
    while(parent != nullptr){
        parent->finddist();
        parent = parent->parent;
    }

    delete forDel;
}

void check(){
    path = LLONG_MIN;
    for(auto it : tree){
        if(it->max == LLONG_MIN){
            if(it->distance > path){
                path = it->distance;
                rootPath = it;
            }
        }else{
            long long temp = it->max + it->sec + it->distance;
            if(temp > path){
                path = temp;
                rootPath = it;
            }
        }
    }
}

int main(){
    cin >> n >> o >> v >> d;
    root = new TN(v, d);
    tree.push_back(root);

    int pi, ci, di;
    while(n--){
        cin >> pi >> ci >> di;
        makeNode(pi, ci, di);
    }

    string op;
    while(o--){
        cin >> op;

        if(op == "Check"){
            check();
            cout << "Maximum Value: " << path << endl;
            cout << "Root of the Path: " << rootPath->val << endl;
        }else if(op == "Add"){
            int parent, node, dist;
            cin >> parent >> node >> dist;
            makeNode(parent, node, dist);
        }else if(op == "Delete"){
            int node;
            cin >> node;
            deleteNode(node);
        }
    }

    check();
    cout << "Final Root: " << rootPath->val << endl;

    return 0;
}