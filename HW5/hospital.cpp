#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Date{
    public:
    int year = 0, month = 0, day = 0;

    Date(){}
    Date(string str){
        if(str == "NaN"){
            year = month = day = 0;
            return;
        }
        
        string s;
        stringstream ss(str);

        getline(ss, s, '-');
        year = stoi(s);
        getline(ss, s, '-');
        month = stoi(s);
        getline(ss, s, '-');
        day = stoi(s);
    }

    int operator>(const Date& date){
        if(year != date.year){
            return year > date.year ? 1 : -1;
        }else if(month != date.month){
            return month > date.month ? 1 : -1;
        }else if(day != date.day){
            return day > date.day ? 1 : -1;
        }

        return 0;
    }
};

class Patient{
public:
    string name;
    Date date;
    int age, money, membership, insertidx;

    Patient(){}
    Patient(string nam, int ag, int mon, int mem, string da, int idx): name(nam) , age(ag), money(mon), membership(mem), insertidx(idx){
        date = Date(da);
    }
};

bool (*FuncPtr)(Patient&, Patient&);

int N, M, P, X, K, idx = 0;
int ag, mon, mem;
string nam, da;
vector<Patient> treatlist;
vector<vector<Patient>::iterator> sorting;
vector<Patient> Pandahospital;

// if right has higher priority than left, return true
bool pandasort(Patient& left, Patient& right){
    if(left.membership != right.membership){
        return left.membership < right.membership;
    }else if(left.date > right.date != 0){
        return left.date > right.date == 1;
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
    for(int i=0; i<hospital.size(); ++i){
        income += hospital[i].money * 0.9;
        cout << hospital[i].name << " " << hospital[i].age << endl;
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