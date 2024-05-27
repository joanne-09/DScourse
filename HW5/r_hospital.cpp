#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <functional>
#include <algorithm>
using namespace std;

class Patient{
public:
    string name, date;
    int age, money, member, id;

    Patient(){};
    Patient(string n, int a, int m, int mem, string d, int i):
        name(n), age(a), money(m), member(mem), date(d), id(i){}
};

struct Panda{
    bool operator()(const Patient& l, const Patient& r){
        if(l.member != r.member){
            return l.member < r.member;
        }else if(l.date != r.date){
            return l.date > r.date;
        }else if(l.name != r.name){
            return l.name > r.name;
        }else{
            return l.id > r.id;
        }
    
        return false;
    }
};

struct Bear{
    bool operator()(const Patient& l, const Patient& r){
        if(l.money != r.money){
            return l.money < r.money;
        }else{
            return l.id > r.id;
        }
    
        return false;
    }
};

int N, M, P, X, K, age, money, member, id = 0;
string name, date;
vector<Patient> treatlist;

long long heapsort(int size, int mode){
    long long income = 0;

    if(mode){
        make_heap(treatlist.begin(), treatlist.end(), Panda());
        
        int s = min((int)treatlist.size(), size);
        for(int i=0; i<s; ++i){
            auto it = treatlist.front();
            income += it.money * 0.9;
            cout << it.name << " " << it.age << endl;

            pop_heap(treatlist.begin(), treatlist.end(), Panda());
            treatlist.pop_back();
        }
    }else{
        make_heap(treatlist.begin(), treatlist.end(), Bear());

        int s = min((int)treatlist.size(), size);
        for(int i=0; i<s; ++i){
            pop_heap(treatlist.begin(), treatlist.end(), Bear());
            treatlist.pop_back();
        }
    }
    return income;
}

int main(){
    cin >> N >> M;
    while(N--){
        cin.ignore();
        getline(cin, name);
        cin >> age >> money >> member >> date;

        treatlist.push_back(Patient(name, age, money, member, date, id));
        ++id;
    }

    for(int i=1; i<=M; ++i){
        cin >> P >> X >> K;
        while(P--){
            cin.ignore();
            getline(cin, name);
            cin >> age >> money >> member >> date;

            treatlist.push_back(Patient(name, age, money, member, date, id));
            ++id;
        }

        cout << "DAY #" << i << endl;
        long long income = 0;

        if(!treatlist.empty() && X) income = heapsort(X, 1);
        if(!treatlist.empty()){
            heapsort(K, 0);
        }

        cout << "INCOME TODAY: " << income << endl;

        //output();
    }

    return 0;
}