#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#define SWAPINT(x, y) {int temp = x; x = y; y = temp;}
using namespace std;

class Pokemon{
public:
    int idx, damage, health, lvl = 1;
    Pokemon *next, *prev;

    Pokemon(int idx, int damage, int health): idx(idx), damage(damage), health(health) {};
};

int num = 0;
list<Pokemon*> poke;

void insert();
bool evolve(int idx, int damage, int health);
void attack(int idx, int damage, int health);
void swap(Pokemon *l, Pokemon *r);
void shuffle();
void check();
void myreverse();
void show();

int main(){
    int n;
    cin >> n;

    string op;
    while(n--){
        cin >> op;
        if(op == "Insert"){
            insert();
        }else if(op == "Delete"){
            if(!poke.empty()){
                poke.pop_front();
                num--;
            }
        }else if(op == "Shuffle"){
            shuffle();
        }else if(op == "Check"){
            check();
        }else if(op == "Reverse"){
            myreverse();
        }else if(op == "Show"){
            show();
        }
    }

    show();
    return 0;
}

void insert(){
    int idx, damage, health;
    string stance;
    cin >> idx >> damage >> health >> stance;

    if(stance == "Evolve" && num >= 2 && evolve(idx, damage, health)) return;
    else if(stance == "Attack" && num > 0){
        attack(idx, damage, health);
        return;
    }

    Pokemon *pokemon = new Pokemon(idx, damage, health);
    poke.push_back(pokemon);
    num++;
}

bool evolve(int idx, int damage, int health){
    auto target = poke.front(), tail = poke.back();
    if(idx != target->idx || idx != tail->idx) return false;
    if(target->lvl == 3 || tail->lvl == 3) return false;

    int maxlvl = max(target->lvl, tail->lvl);
    int maxdamage = max(damage, max(target->damage, tail->damage));
    int maxhealth = max(health, max(target->health, tail->health));

    target->lvl = maxlvl+1, target->damage = maxdamage, target->health = maxhealth;
    poke.pop_back();
    num--;
    return true;
}

void attack(int idx, int damage, int health){
    auto target = poke.front(), tail = poke.back(), pokemon = new Pokemon(idx, damage, health);
    if(target != tail){
        tail->health -= damage;
        if(tail->health <= 0){
            poke.pop_back();
            num--;
        }
    }
    
    target->health -= damage;
    if(target->health <= 0){
        poke.pop_front();
        poke.push_front(pokemon);
        return;
    }

    poke.push_back(pokemon);
    num++;
}

void swap(Pokemon *l, Pokemon *r){
    if(l == r) return;
    SWAPINT(l->idx, r->idx);
    SWAPINT(l->damage, r->damage);
    SWAPINT(l->health, r->health);
    SWAPINT(l->lvl, r->lvl);
}

void shuffle(){
    char dir;
    int step;

    cin >> dir >> step;
    step %= num;

    Pokemon *target = poke.front();
    auto it = poke.begin();
    if(dir == 'a') step = num-step;

    poke.splice(poke.end(), poke, it, next(it, step));

    swap(target, poke.front());
}

void check(){
    map<int, int> hm;
    int step;
    cin >> step;

    step = min(num, step);
    auto it = poke.begin();

    for(int i=0; i<step; i++){
        hm[(*it)->idx]++;
        it++;
    }

    it = poke.begin();
    for(int i=0; i<step; i++){
        if(hm[(*it)->idx] > 1){
            it = poke.erase(it);
            num--;
        }else it++;
    }
}

void myreverse(){
    int cnt, times;
    cin >> cnt;
    cnt = min(num, cnt), times = num/cnt;

    list<Pokemon*> temp;
    auto it = poke.begin();
    for(; it != poke.end() && times > 0; --times){
        reverse(it, next(it, cnt));
        advance(it, cnt);
    }
    reverse(it, poke.end());
}

void show(){
    if(poke.empty()){
        cout << "no Poke Poke ;-;\n";
    }else{
        for(auto it : poke){
            cout << "ID: " << it->idx << " HP: " << it->health << " LVL: " << it->lvl << endl; 
        }
    }
}