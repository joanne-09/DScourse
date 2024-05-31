#include <iostream>
#include <vector>
using namespace std;

void Mergesort(vector<int>& arr, int size){
    if(size < 2) return;
    
    // divide array into two parts
    int mid = size/2;
    vector<int> left(arr.begin(), arr.begin()+mid);
    vector<int> right(arr.begin()+mid, arr.end());

    // sort left and right parts recursively
    Mergesort(left, mid);
    Mergesort(right, size-mid);

    // merge left and right parts together
    int i = 0, j = 0, k = 0;
    while(i < mid && j < size-mid){
        if(left[i] < right[j]){
            arr[k++] = left[i++];
        }else{
            arr[k++] = right[j++];
        }
    }

    // check if there are any elements left
    while(i < mid){
        arr[k++] = left[i++];
    }

    while(j < size-mid){
        arr[k++] = right[j++];
    }
}

void Output(vector<int>& arr){
    for(auto& it : arr)
        cout << it << " ";
    cout << endl;
}

int main(){
    vector<int> data = {26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    Mergesort(data, data.size());
    Output(data);

    return 0;
}