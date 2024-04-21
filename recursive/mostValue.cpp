#include <iostream>

struct Item{
    int weight;
    int value;
}items[105];

int n, k, max=0;

void rec(int cur, int idx, int val){
    if(val > max) max=val;
    for(int i=idx; i<n; i++){
        if(cur+items[i].weight <= k)
            rec(cur+items[i].weight, i+1, val+items[i].value);
    }
}

int main(){
    std::cin >> n >> k;
    for(int i=0; i<n; ++i){
        std::cin >> items[i].value >> items[i].weight;
    }
    rec(0, 0, 0);
    std::cout << max << std::endl;
}