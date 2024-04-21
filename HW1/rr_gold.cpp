#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Miner{
public:
    vector<char> bag;
    queue<char> invent;

    int findLevel(int col);
    void dig(int col);
    void use();
    void flash();
    void bomb(int row, int col);
    void clover(int col);
    void pig();
    void printBag();
};

int r, l, n;
char map[205][105];
Miner miner;

void printMap(){
    int level = 0;
    for(int i=0; i<r; i++){
        int size = miner.findLevel(i);

        level = level > size ? level : size;
    }


    cout << "FINAL MAP:\n";
    if(!level) return;

    for(int j=level; j>0; j--){
        for(int i=0; i<r; i++){
            cout << map[j][i] << " ";
        }
        cout << endl;
    }
}

int main(){
    cin >> r >> l >> n;

    for(int i=0; i<r; i++) map[0][i] = '_';

    for(int i=l; i>0; i--){
        for(int j=0; j<r; j++){
            cin >> map[i][j];
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
    for(int i=l; i>0; i--){
        if(map[i][col] != '_'){
            return i;
        }
    }

    return 0;
}

void Miner::dig(int col){
    if(col<0 || col>=r) return;
    int level = findLevel(col);

    if(!level) return;

    char item = map[level][col];
    map[level][col] = '_';

    switch(item){
        case 'D': case 'G':
            bag.push_back(item);
            break;
        case 'F': case 'M':
            invent.push(item);
            break;
        case 'B':
            bomb(level, col);
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

    if(item == 'F'){
        flash();
    }else if(item == 'M'){
        for(int i=0; i<r; i++) dig(i);
    }
}

void Miner::flash(){
    int level = 0;
    for(int i=0; i<r; i++){
        int size = findLevel(i);
        level = level>size ? level : size;
    }

    l = level;
    cout << "MINE LEVEL:" << (level==0 ? 1 : level) << endl;
    for(int i=0; i<r; i++){
        cout << map[level][i] << " ";
    }
    cout << endl;
}

void Miner::bomb(int row, int col){
    for(int i=row-1; i<=row+1; i++){
        if(i<=0 || i>l) continue;
        for(int j=col-1; j<=col+1; j++){
            if(j<0 || j>=r) continue;

            map[i][j] = '_';
        }
    }
}

void Miner::clover(int col){
    if(bag.empty()) return;

    char item = bag[bag.size()-1];

    int level = 0;
    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;
        int size = findLevel(i);

        level = level>size ? level : size;
    }

    if(!level) return;

    for(int i=0; i<r; i++){
        map[level+1][i] = '_';
        map[level+2][i] = '_';
        map[level+3][i] = '_';
    }

    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;

        map[level+1][i] = item;
        map[level+2][i] = item;
        map[level+3][i] = item;
    }

    l = level+3;
}

void Miner::pig(){
    while(!bag.empty() && bag[bag.size()-1] != 'D'){
        bag.pop_back();
    }
}

void Miner::printBag(){
    cout << "FINAL BAG:\n";

    if(bag.empty()){
        cout << endl;
        return;
    }

    for(int i=0; i<bag.size(); i++){
        cout << bag[i] << " ";
    }

    cout << endl;
}