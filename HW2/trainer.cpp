#include <iostream>
#include <string>
#define MAX(x, y, z) (x>y ? (x>z ? x : (y>z ? y : z)) : (y>z ? y : (z>x ? z : x)))
using namespace std;

class Pokemon{
private:
    int id, lvl = 1, damageVal, healthVal;
    string stance;

public:
    Pokemon *next = nullptr, *prev = nullptr;

    inline int getid() {return id;}
    inline int getDamageVal() {return damageVal;}
    inline int getHealthVal() {return healthVal;}
    inline string getStr() {return stance;}
    inline int getLvl() {return lvl;}
    inline void update(int dam, int health, int l) {damageVal = dam; healthVal = health; lvl = l;}
    inline void updateHeal(int num) {healthVal -= num;}
    inline void updateStr(string str) {stance = str;}

    Pokemon(int poke, int damage, int health, string stan){
        id = poke;
        damageVal = damage;
        healthVal = health;
        stance = stan;
    }

};

int n, num = 0;
string op;
Pokemon *target = nullptr;

void insert();
bool evolve(int id, int dam, int heal, string str);
void attack(Pokemon *check);
void del(Pokemon *temp);
void swapNode(Pokemon *l, Pokemon *r);
void shuffle();
void check();
void reverseNode(Pokemon *start, Pokemon *end, int a);
void reverse();
void printPoke();

int main(){
    cin >> n ;

    while(n--){
        cin >> op ;

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
        }
    }

    printPoke();

    return 0;
}

// neutral mode: done
void insert(){
    int a, b, c;
    string str;
    cin >> a >> b >> c >> str ;

    if(evolve(a, b, c, str)) return;

    Pokemon *pokemon = new Pokemon(a, b, c, str);

    if(!target){
        target = pokemon;
        target -> next = target -> prev = target;
    }else{
        pokemon -> next = target;
        target -> prev -> next = pokemon;
        pokemon -> prev = target -> prev;
        target -> prev = pokemon;
    }

    num++;

    if(str == "Attack"){
        attack(pokemon);
        pokemon->updateStr("Neutral");
    }
}

bool evolve(int id, int dam, int heal, string str){
    if(!target || target == target->prev) return false;

    if(str != "Evolve") return false;
    if(id != target->getid()) return false;
    if(id != target->prev->getid()) return false;
    if(target->prev->getLvl() >= 3 || target->getLvl() >= 3) return false;

    int attack = MAX(dam, target->getDamageVal(), target->prev->getDamageVal());
    int health = MAX(heal, target->getHealthVal(), target->prev->getHealthVal());
    int lvl = MAX(1, target->prev->getLvl(), target->getLvl());

    target->update(attack, health, lvl+1);

    del(target->prev);
    return true;
}

void attack(Pokemon *check){
    if(check == target) return;

    if(check->prev != check->next){
        if(check->prev->getHealthVal() <= check->getDamageVal()){
            del(check->prev);
        }else
            check->prev->updateHeal(check->getDamageVal());
    }

    if(check->next->getHealthVal() <= check->getDamageVal()){
        del(check->next);
        target = check;
    }else{
        check->next->updateHeal(check->getDamageVal());
    }
}

// done
void del(Pokemon *temp){
    if(!temp) return;

    Pokemon *forDel = temp;
    num--;

    if(temp == target && target->next == target){
        target = nullptr;
        delete forDel;
        return;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    if(temp == target) target = temp->next;
 
    delete forDel;
}

// done
void swapNode(Pokemon *l, Pokemon *r){
    if(l == r) return;

    Pokemon *temp = r->prev;
    r->prev = l->prev;
    l->prev = temp;

    l->prev->next = l;
    r->prev->next = r;

    temp = r->next;
    r->next = l->next;
    l->next = temp;

    l->next->prev = l;
    r->next->prev = r;
}

// done
void shuffle(){
    char ch;
    int a;
    cin >> ch >> a;

    a %= num;

    Pokemon *cur = target;
    if(ch == 'c'){
        while(a--){
            cur = cur->next;
        }
    }else if(ch == 'a'){
        while(a--){
            cur = cur->prev;
        }
    }
    
    swapNode(cur, target);
}

// done
void check(){
    int a;
    cin >> a;

    if(a == 1) return;
    if(target == target->next || !target) return;

    Pokemon *end = target, *cur = target;
    int targetflag = 0, endflag = 0;

    while(--a){
        end = end->next;
    }

    while(cur != end){
        int flag = 0;
        Pokemon *temp = cur->next;

        while(1){
            if(temp->getid() == cur->getid()){
                flag = 1;
                Pokemon *forDel = temp;
                if(temp == end){
                    endflag = 1;
                    break;
                }

                temp = temp->next;
                del(forDel);
            }else{
                if(temp == end) break;
                temp = temp->next;
            }
        }

        if(flag){
            if(cur == target){
                targetflag = 1;
                cur = cur->next;
            }else{
                Pokemon *forDel = cur;
                cur = cur->next;
                del(forDel);
            }
        }else cur = cur->next;
    }

    if(targetflag) del(target);
    if(endflag) del(end);
}

// done
void reverseNode(Pokemon *start, Pokemon *end, int a){
    Pokemon *cur = start, *curend = end, *change1, *change2;
    for(int i=0; i<a/2; i++){
        change1 = cur, change2 = curend;
        cur = cur->next;
        curend = curend->prev;

        swapNode(change1, change2);
    }

    if(start == target) target = end;
}

// done
void reverse(){
    int a;
    cin >> a;

    if(a==1) return;
    if(target == target->next || !target) return;

    Pokemon *cur = target;
    while(cur){
        Pokemon *start = cur;
        int count = 1;

        for(int i=0; i<a-1; i++){
            if(cur == target->prev) break;
            cur = cur->next;
            count++;
        }
        
        if(start != cur) reverseNode(start, cur, count);
        cur = start;

        cur = cur->next;
        if(cur == target) break;
    }
}

// done
void printPoke(){
    Pokemon *cur = target;

    if(!cur){
        cout << "no Poke Poke ;-;\n";
        return;
    }

    while(cur){
        cout << "ID: " << cur->getid() << " HP: " << cur->getHealthVal() << " LVL: " << cur->getLvl() << endl;
        cur = cur->next;
        
        if(cur == target) break;
    }
}