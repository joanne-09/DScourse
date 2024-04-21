#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
using namespace std;

class Miner{
public:
    queue<char> invent;
    stack<char> bag;

    int findLevel(int col);
    void dig(int col);
    void use();
    void flash();
    void magnet();
    void bomb(int col, int row);
    void clover(int col);
    void pig();

    void printBag();
};

int r, l, n;
int dir[][2] = {{1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}};
vector<vector<char>> map;
Miner miner;

void printMap(){
    cout << "FINAL MAP:\n";
    int level = 0;
    for(int i=0; i<r; i++){
        int size = miner.findLevel(i);

        level = level>size+1 ? level : size+1;
    }
    for(int i=level-1; i>=0; i--){
        for(int j=0; j<r; j++){
            cout << map[j][i] << " ";
        }
        cout << endl;
    }
}

int main(){
    cin >> r >> l >> n;

    map.resize(r);
    for(int i=0; i<r; i++) map[i].resize(l+3, '_');

    for(int i=l-1; i>=0; i--){
        for(int j=0; j<r; j++){
            cin >> map[j][i];
        }
    }

    string action;
    while(n--){
        cin >> action;

        if(action == "DIG"){
            int col;
            cin >> col;
            miner.dig(col);
        }else if(action == "USE"){
            miner.use();
        }
    }

    miner.printBag();
    printMap();

    return 0;
}

int Miner::findLevel(int col){
    for(int i=l-1; i>=0; i--){
        if(map[col][i] != '_'){
            return i;
        }
    }

    return -1;
}

void Miner::dig(int col){
    if(col >=r || col<0) return;

    char item = '_';
    int row = findLevel(col);

    if(row != -1){
        item = map[col][row];
        map[col][row] = '_';
    }else return;

    switch(item){
        case 'D': case 'G':
            bag.push(item);
            break;
        case 'B':
            bomb(col, row);
            break;
        case 'F': case 'M':
            invent.push(item);
            break;
        case 'C':
            clover(col);
            break;
        case 'P':
            pig();
            break;
        default:
            return;
    }
}

void Miner::use(){
    if(invent.empty()) return;

    char item = invent.front();
    invent.pop();

    switch (item){
        case 'F':
            flash();
            break;
        case 'M':
            magnet();
            break;
        default:
            return;
    }
}

void Miner::flash(){
    int level = 0;
    for(int i=0; i<r; i++){
        int size = findLevel(i);

        level = level>size ? level : size;
    }

    if(!level){
        cout << "MINE LEVEL:1\n";
        for(int i=0; i<r; i++) cout << "_ ";
        l = 0;
        cout << endl;
        return;
    }

    cout << "MINE LEVEL:" << level+1 << endl;
    for(int i=0; i<r; i++){
        cout << map[i][level] << " ";
    }
    cout << endl;

    l = level + 1;
}

void Miner::magnet(){
    for(int i=0; i<r; i++) dig(i);
}

void Miner::bomb(int col, int row){
    for(int i=0; i<8; i++){
        int newC = col+dir[i][0], newR = row+dir[i][1];
        if(newC<0 || newC>=r || l<=newR || newR<0) continue;

        map[newC][newR] = '_';
    }
}

void Miner::clover(int col){
    if(bag.empty()) return;

    char item = bag.top();
    int level = 0;
    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;

        int size = findLevel(i);
        level = level>size ? level : size;
    }

    if(level == 0) return;

    l = l>level+4 ? l : level+4;

    for(int i=0; i<r; i++){
        map[i].resize(l, '_');
    }

    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;

        for(int j=1; j<=3; j++){
            map[i][j+level] = item;
        }
    }
}

void Miner::pig(){
    while(!bag.empty() && bag.top()!='D'){
        bag.pop();
    }
}

void Miner::printBag(){
    cout << "FINAL BAG:\n";
    if(bag.empty()){
        cout << endl;
        return;
    }

    stack<char> temp;
    int len = bag.size();

    for(int i=0; i<len; i++){
        temp.push(bag.top());
        bag.pop();
    }

    for(int i=0; i<len; i++){
        cout << temp.top() << " ";
        temp.pop();
    }

    cout << endl;
}