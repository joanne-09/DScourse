#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Date{
    public:
    int year, month, day;

    Date(){}
    Date(string str){
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
    int age, money, membership;

    Patient(string nam, int ag, int mon, int mem, string da): name(nam) , age(ag), money(mon), membership(mem){
        date = Date(da);
    }

    // if true: than higher priority
    bool operator>(const Patient& patient){
        if(membership != patient.membership){
            return membership > patient.membership;
        }else if(date > patient.date != 0){
            return date > patient.date == 1;
        }
    }
};

int N, M, P, X, K;
int ag, mon, mem;
string nam, da;
vector<Patient> hospital(4000);

int main(){
    cin >> N >> M;
    while(N--){
        getline(cin, nam);
        cin >> ag >> mon >> mem >> da;

        hospital.push_back(Patient(nam, ag, mon, mem, da));
    }

    for(int i=1; i<=M; ++i){
        cin >> P >> X >> K;
        while(P--){
            getline(cin, nam);
            cin >> ag >> mon >> mem >> da;
        }
    }
    return 0;
}