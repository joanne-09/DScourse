#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <functional>
#include <algorithm>
#include <climits>
#include <cmath>
#include <utility>
using namespace std;

int N;
vector<int> l;
vector<int> inversion(200005, 0);

int quicksort(vector<int> vec){
    if(vec.size() <= 1){
        return 1;
    }

    vector<int> left, right;
    int pivot = vec[0];
    for(int i=1; i<vec.size(); ++i){
        if(vec[i] < pivot){
            left.push_back(vec[i]);
        }else{
            right.push_back(vec[i]);
        }
    }

    return 1 + quicksort(left) + quicksort(right);
}

int main(){
    cin >> N;
    for(int i=1; i<=N; ++i){
        int temp;
        cin >> temp;

        l.push_back(temp);
    }

    int cnt = 0;
    /*for(int i=0; i<N-1; ++i){
        int target = l[i+1];
        for(int j=i+1; j<N; ++j){
            if(l[i] > l[j]){
                cnt++;
            }
        }
    }*/

    for(int i=N-2; i>=0; --i){
        int target = l[i+1];
        for(int j=i+1; j<N; ++j){
            if(l[j] < target || l[j] > l[i]) continue;
            else if(l[j] >= target){
                target = l[j];
                inversion[i] += 1 + inversion[target];
            }
        }

        cnt += inversion[i];
    }

    cout << cnt << endl;
    return 0;
}