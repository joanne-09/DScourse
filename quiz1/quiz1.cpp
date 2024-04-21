#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
using namespace std;

class Miner{
public:
    int virus = 0;
    vector<char> invent;
    vector<char> bag;
    int coin = 0;

    void dig(int col);
    void use();
    void printBag();
    void printInvent();
    void pig();
};

int r, l, n, lastcol = -1, extra = 0;
vector<queue<char>> map;
Miner miner;

void printMap(){
    cout << "Map:\n";

    for(int i=0; i<l; i++){
        if(map[i].size() < r+extra){
            for(int j=0; j<(r+extra-map[i].size()); j++){
                cout << "_ ";
            }
            int con = map[i].size();
            for(int j=0; j<con; j++){
                cout << map[i].front() << " ";
                map[i].pop();
            }
            cout << endl;
        }else{
            for(int j=0; j<r+extra; j++){
                cout << map[i].front() << " ";
                map[i].pop();
            }
            cout << endl;
        }
    }
}

int main(){
    cin >> r >> l >> n;

    for(int i=0; i<l; i++){
        queue<char> store;
        for(int j=0; j<r; j++){
            char temp;
            cin >> temp;

            store.push(temp);
        }
        map.push_back(store);
    }

    string action;
    while(n--){
        cin >> action;

        if(action == "DIG"){
            int col;
            cin >> col;

            miner.dig(col);

            lastcol = col;
        }else if(action == "USE"){
            miner.use();
        }

        if(miner.virus == 1) break;
    }

    miner.printBag();
    miner.printInvent();
    printMap();

    return 0;
}

void Miner::dig(int col){
    if(col<0 || col>=l) return;

    if(map[col].empty()) return;

    char item = map[col].front();
    map[col].pop();

    switch(item){
        case 'D': case 'G':
            bag.push_back(item);
            break;
        case 'S': case 'X':
            invent.push_back(item);
            break;
        case 'C':
            coin = 1;
            break;
        case 'V':
            virus = 1;
            cout << "Game Over!\n";
            break;
        case 'P':
            pig();
            break;
        default:
            break;
    }
}

void Miner::use(){
    if(invent.empty()) return;

    char item = invent[invent.size()-1];
    invent.pop_back();

    if(item == 'S'){
        if(lastcol == -1) return;
        dig(lastcol);
        if(virus) return;
        dig(lastcol);
    }else if(item == 'X'){
        for(int i=0; i<l; i++){
            if((i+1)%2 == 0) map[i].push('G');
            else map[i].push('D');
        }
        extra ++;
    }
}

void Miner::printBag(){
    cout << "Backpack:";
    if(bag.empty()){
        cout << endl;
        return;
    }

    for(int i=0; i<bag.size(); i++){
        cout << " " << bag[i];
    }
    cout << endl;
}

void Miner::printInvent(){
    cout << "Inventory:";
    if(invent.empty()){
        cout << endl;
        return;
    }

    for(int i=0; i<invent.size(); i++){
        cout << " " << invent[i];
    }
    cout << endl;
}

void Miner::pig(){
    if(bag.empty()) return;

    if(coin){
        coin = 0;
        cout << "Ding!\n";
        return;
    }

    vector<char> temp;
    for(int i=0; i<bag.size(); i++){
        if(bag[i] == 'D'){
            temp.push_back('D');
        }
    }
    bag = temp;
}