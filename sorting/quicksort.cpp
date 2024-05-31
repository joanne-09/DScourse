#include <iostream>
#include <vector>
using namespace std;

void Quicksort(vector<int>& arr, int left, int right){
    if(left >= right) return;
    int pivot = arr[left];

    int i = left+1, j = right;
    do{
        while(arr[i] < pivot) ++i;
        while(arr[j] > pivot) --j;

        if(i < j) swap(arr[i], arr[j]);
    }while(i < j);

    swap(arr[j], arr[left]);

    Quicksort(arr, left, j-1);
    Quicksort(arr, j+1, right);
}

void Output(vector<int>& arr){
    for(auto& it : arr)
        cout << it << " ";
    cout << endl;
}

int main(){
    vector<int> data = {26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    Quicksort(data, 0, data.size()-1);
    Output(data);

    return 0;
}