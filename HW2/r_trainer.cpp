#include <iostream>
#include <string>
using namespace std;

class Data{
public:
    int idx, damage, health, lvl = 1;
    void output(){
        cout << "ID: " << idx << " HP: " << health << " LVL: " << lvl << endl;
    }
};

class Pokemon{
public:
    Data data;
    Pokemon *next = nullptr, *prev = nullptr;

    Pokemon(int idx, int damage, int health){
        data.idx = idx;
        data.damage = damage;
        data.health = health;
    }
};

int num = 0;
Pokemon *target = nullptr;

void insert();
bool evolve(int idx, int damage, int health, string stance);
void attack(Pokemon *check);
void del(Pokemon *temp);
void swapNode(Pokemon* l, Pokemon* r);
void shuffle();
void check();
void reverseNodes(Pokemon *start, Pokemon *end);
void reverse();
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
            del(target);
        }else if(op == "Shuffle"){
            shuffle();
        }else if(op == "Check"){
            check();
        }else if(op == "Reverse"){
            reverse();
        }else if(op == "Show"){
            show();
        }
    }

    show();
}

void insert(){
    int idx, damage, health;
    string stance;

    cin >> idx >> damage >> health >> stance;

    if(evolve(idx, damage, health, stance)) return;
    
    Pokemon *pokemon = new Pokemon(idx, damage, health);

    if(!target){
        target = pokemon;
        target->next = target->prev = target;
    }else{
        pokemon->next = target;
        pokemon->prev = target->prev;
        pokemon->prev->next = pokemon;
        target->prev = pokemon;
    }
    
    num++;
    if(stance == "Attack") attack(pokemon);
}

bool evolve(int idx, int damage, int health, string stance){
    if(stance != "Evolve") return false;
    if(!target || target == target->prev) return false;
    if(target->data.idx != target->prev->data.idx) return false;
    if(target->data.idx != idx) return false;
    if(target->data.lvl >= 3 || target->prev->data.lvl >= 3) return false;

    int finLvl = max(1, max(target->data.lvl, target->prev->data.lvl));
    int finDamage = max(damage, max(target->data.damage, target->prev->data.damage));
    int finHealth = max(health, max(target->data.health, target->prev->data.health));

    target->data.lvl = finLvl+1, target->data.damage = finDamage, target->data.health = finHealth;
    del(target->prev);

    return true;
}

void attack(Pokemon *check){
    if(check == target) return;
    if(check->prev != check->next){
        if(check->data.damage >= check->prev->data.health){
            del(check->prev);
        }else{
            check->prev->data.health -= check->data.damage;
        }
    }

    if(check->data.damage >= check->next->data.health){
        del(check->next);
        target = check;
    }else{
        check->next->data.health -= check->data.damage;
    }
}

void del(Pokemon *temp){
    if(!temp) return;

    Pokemon *forDel = temp;
    num--;

    if(temp == target){
        if(num == 0){
            target = nullptr;
            delete(forDel);
            return;
        }else target = target->next;
    }

    
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    delete(forDel);
}

void shuffle(){
    char dir;
    int times;
    Pokemon *cur = target;

    cin >> dir >> times;
    times %= num;

    if(dir == 'c'){
        while(times--){
            cur = cur->next;
        }
    }else if(dir == 'a'){
        while(times--){
            cur = cur->prev;
        }
    }

    swapNode(target, cur);
    target = cur;
}

void swapNode(Pokemon *l, Pokemon *r){
    if(l == r) return;

    Data temp = l->data;
    l->data = r->data;
    r->data = temp;
}

void check(){
    int times;
    cin >> times;

    times = min(num, times);
    Pokemon *end = target, *cur = target, *change = cur->next;
    int targetflag = 0, endflag = 0, flag = 0;

    while(--times){
        end = end->next;
    }

    while(cur != end){
        change = cur->next;
        flag = 0;
        while(change != end){
            if(cur->data.idx == change->data.idx){
                flag = 1;
                Pokemon *temp = change;
                change = change->next;
                del(temp);
            }else change = change->next;
        }
        if(cur->data.idx == end->data.idx) flag = endflag = 1;

        if(flag){
            if(cur == target){
                targetflag = 1;
                cur = cur->next;
            }else{
                Pokemon *temp = cur;
                cur = cur->next;
                del(temp);
            }
        }else cur = cur->next;
    }
    
    if(targetflag) del(target);
    if(endflag) del(end);
    
}

void reverseNodes(Pokemon *start, Pokemon *end){
    int count = 1;
    Pokemon *cur = start;
    while(cur != end){
        count++;
        cur = cur->next;
    }

    for(int i=0; i<count/2; i++){
        swapNode(start, end);
        start = start->next;
        end = end->prev;
    }
}

void reverse(){
    int group, times;
    cin >> group;

    group = min(num, group), times = num/group;
    Pokemon *cur = target, *start = target;

    while(times--){
        start = cur;
        for(int i=0; i<group-1; i++){
            cur = cur->next;
        }

        reverseNodes(start, cur);
        cur = cur->next;
    }

    if(cur != target && cur != target->prev){
        reverseNodes(cur, target->prev);
    }
}

void show(){
    Pokemon *cur = target;

    if(!cur){
        cout << "no Poke Poke ;-;\n";
    }else{
        while(cur){
            cur->data.output();
            cur = cur->next;
            if(cur == target) break;
        }
    }
}