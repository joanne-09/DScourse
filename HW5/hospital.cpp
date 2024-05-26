#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

using std::cout;
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
    }else if(left.membership == 1 && left.date != right.date){
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

long long heapsort(vector<Patient>& hospital, int size, int mode){
    long long income = 0;
    for(int i=1; i<hospital.size(); ++i){
        int j = i;
        while(j > 0 && !FuncPtr(hospital[j], hospital[(j-1)/2])){
            swap(hospital[j], hospital[(j-1)/2]);
            j = (j-1)/2;
        }
    }

    for(int i=hospital.size()-1; i>=0 && size>0; --i, --size){
        if(mode){
            income += hospital[0].money * 0.9;
            cout << hospital[0].name << " " << hospital[0].age << endl;
        }
        
        if(i == 0) break;
        swap(hospital[0], hospital[i]);
        int j = 0;
        while(2*j+1 < i){
            int k = 2*j+1;
            if(k+1 < i && FuncPtr(hospital[k], hospital[k+1])){
                ++k;
            }
            if(FuncPtr(hospital[j], hospital[k])){
                swap(hospital[j], hospital[k]);
                j = k;
            }else{
                break;
            }
        }
    }

    return income;
}

int main(){
    cin >> N >> M;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
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

        cout << "DAY #" << i << endl;
        long long income = 0;
        FuncPtr = pandasort;
        
        if(treatlist.size() <= X){
            income = heapsort(treatlist, treatlist.size(), 1);
            treatlist.clear();
        }else{
            income = heapsort(treatlist, X, 1);
            treatlist.erase(treatlist.begin()+(treatlist.size()-X), treatlist.end());

            if(treatlist.size() <= K){
                treatlist.clear();
            }else if(K != 0){
                FuncPtr = bearsort;
                heapsort(treatlist, K, 0);
                treatlist.erase(treatlist.begin()+(treatlist.size()-K), treatlist.end());
            }
        }

        //cout << "DAY #" << i << endl;
        //long long income = output(Pandahospital);
        cout << "INCOME TODAY: " << income << endl;
    }
    return 0;
}