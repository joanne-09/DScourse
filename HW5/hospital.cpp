#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Patient{
public:
    string name;
    string date;
    int age, money, membership, insertidx;

    Patient(){}
    Patient(string nam, int ag, int mon, int mem, string da, int idx): name(nam) , age(ag), money(mon), membership(mem), insertidx(idx){
        date = da;
    }
};

bool (*FuncPtr)(Patient&, Patient&);

int N, M, P, X, K, idx = 0;
int ag, mon, mem;
string nam, da;
vector<Patient> treatlist;
vector<Patient> Pandahospital;

// if right has higher priority than left, return true
bool pandasort(Patient& left, Patient& right){
    if(left.membership != right.membership){
        return left.membership < right.membership;
    }else if(left.date != right.date){
        return left.date > right.date;
    }else if(left.name != right.name){
        return left.name > right.name;
    }else{
        return left.insertidx > right.insertidx;
    }

    return false;
}

bool bearsort(Patient& left, Patient& right){
    if(left.money != right.money)
        return left.money < right.money;
    else
        return left.insertidx > right.insertidx;

    return false;
}

void heapsort(vector<Patient>& hospital){
    for(int i=1; i<hospital.size(); ++i){
        int j = i;
        while(j > 0 && FuncPtr(hospital[j], hospital[(j-1)/2])){
            swap(hospital[j], hospital[(j-1)/2]);
            j = (j-1)/2;
        }
    }

    for(int i=hospital.size()-1; i>0; --i){
        swap(hospital[0], hospital[i]);
        int j = 0;
        while(2*j+1 < i){
            int k = 2*j+1;
            if(k+1 < i && !FuncPtr(hospital[k], hospital[k+1])){
                ++k;
            }
            if(!FuncPtr(hospital[j], hospital[k])){
                swap(hospital[j], hospital[k]);
                j = k;
            }else{
                break;
            }
        }
    }
}

long long output(vector<Patient>& hospital){
    long long income = 0;
    for(auto& it : hospital){
        income += it.money * 0.9;
        cout << it.name << " " << it.age << endl;
        //cout << it.money << " " << it.membership << endl;
    }

    return income;
}

int main(){
    cin >> N >> M;
    while(N--){
        cin.ignore();
        getline(cin, nam);
        cin >> ag >> mon >> mem >> da;

        treatlist.push_back(Patient(nam, ag, mon, mem, da, idx));
        ++idx;
    }

    for(int i=1; i<=M; ++i){
        cin >> P >> X >> K;
        while(P--){
            cin.ignore();
            getline(cin, nam);
            cin >> ag >> mon >> mem >> da;

            treatlist.push_back(Patient(nam, ag, mon, mem, da, idx));
            ++idx;
        }

        FuncPtr = pandasort;
        heapsort(treatlist);

        if(treatlist.size() < X){
            Pandahospital.assign(treatlist.begin(), treatlist.end());
            treatlist.clear();
        }else{
            Pandahospital.assign(treatlist.begin(), treatlist.begin()+X);
            treatlist.erase(treatlist.begin(), treatlist.begin()+X);

            if(treatlist.size() < K){
                treatlist.clear();
            }else{
                FuncPtr = bearsort;
                heapsort(treatlist);
                treatlist.erase(treatlist.begin(), treatlist.begin()+K);
            }
        }

        cout << "DAY #" << i << endl;
        long long income = output(Pandahospital);
        cout << "INCOME TODAY: " << income << endl;
    }
    return 0;
}