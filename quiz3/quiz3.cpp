#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class TN{
public:
    int val;
    TN *lc = nullptr, *rc = nullptr, *parent = nullptr;

    TN(int v): val(v){};

    int addChild(int val){
        if(!lc){
            lc = new TN(val);
            lc->parent = this;
            return 1;
        }else if(!rc){
            rc = new TN(val);
            rc->parent = this;
            return 2;
        }

        return 0;
    }
    void addChild1(TN* val){
        if(!lc){
            lc = val;
            val->parent = this;
        }else if(!rc){
            rc = val;
            val->parent = this;
        }
    }
    void removeChild(TN* val){
        if(lc == val) lc = nullptr;
        else if(rc == val) rc = nullptr;
    }
};

int n, ops, capacity = 200, s;
int a, b, c;
vector<TN*> trees(200, nullptr);

TN* dfs(TN* root, int val){
    if(!root) return nullptr;

    if(root->val == val) return root;
    TN* left = dfs(root->lc, val);
    TN* right = dfs(root->rc, val);

    if(left) return left;
    if(right) return right;

    return nullptr;
}

void insert(){
    int idx, par, val;
    cin >> idx >> par >> val;

    if(idx >= n) return;
    if(!trees[idx]){
        trees[idx] = new TN(val);
        return;
    }

    TN *parent = nullptr, *child = nullptr;
    parent = dfs(trees[idx], par);

    if(!parent) return;
    parent->addChild(val);
}

void inorder(TN* root){
    if(!root) return;
    inorder(root->lc);
    cout << root->val << " ";
    inorder(root->rc);
}

void preorder(TN* root){
    if(!root) return;
    cout << root->val << " ";
    preorder(root->lc);
    preorder(root->rc);
}

void postorder(TN* root){
    if(!root) return;
    postorder(root->lc);
    postorder(root->rc);
    cout << root->val << " ";
}

void print(){
    int idx;
    string mode;
    cin >> idx >> mode;

    if(mode == "in"){
        inorder(trees[idx]);
    }else if(mode == "pre"){
        preorder(trees[idx]);
    }else if(mode == "post"){
        postorder(trees[idx]);
    }
    cout << endl;
}

int Max = INT_MIN;
int dfs1(TN* root){
    if(!root) return INT_MIN;

    if(root->val > Max) Max = root->val;
    dfs1(root->lc);
    dfs1(root->rc);
}

void max(){
    int idx, len;
    cin >> idx;

    if(!trees[idx]) return;
    Max = INT_MIN;
    dfs1(trees[idx]);

    cout << Max << endl;
}

void merge(){
    int des, from , val;
    cin >> des >> from >> val;

    TN* newroot = new TN(val);
    if(trees[des]) {newroot->lc = trees[des]; trees[des]->parent = newroot;}
    if(trees[from]) {newroot->rc = trees[from]; trees[from]->parent = newroot;}

    trees[des] = newroot;
    trees[from] = nullptr;
}

void disjoint(){
    int idx, val;
    cin >> idx >> val;

    TN* target = dfs(trees[idx], val);
    if(!target) return;
    if(target == trees[idx]) trees[idx] = nullptr;

    int i = 0;
    for(; i<capacity; ++i){
        if(!trees[i]) break;
    }

    n = n > i+1 ? n : i+1;
    trees[i] = target;
    if(!target->parent) return;
    target->parent->removeChild(target);
    target->parent = nullptr;
}

void delrec(TN* root){
    if(!root) return;
    delrec(root->lc);
    delrec(root->rc);
    delete(root);
}

void del(){
    int idx, val, flag = 0;
    cin >> idx >> val;

    TN* target = dfs(trees[idx], val);
    if(!target) return;

    if(target == trees[idx]) flag = 1;
    if(target->parent) target->parent->removeChild(target);
    delrec(target);

    if(flag) trees[idx] = nullptr;
    //if(idx == n-1 && n > s) n--;
}

void final(){
    for(int i=0; i<n; ++i){
        //if(!trees[i]) continue;
        cout << "Tree " << i << endl;
        inorder(trees[i]);
        cout << endl;
    }
}

int main(){
    cin >> s >> ops;
    n = s;

    string op;
    while(ops--){
        cin >> op;
        if(op == "Insert"){
            insert();
        }else if(op == "Print"){
            print();
        }else if(op == "Max"){
            max();
        }else if(op == "Merge"){
            merge();
        }else if(op == "Disjoint"){
            disjoint();
        }else if(op == "Delete"){
            del();
        }
    }
    final();
    return 0;
}