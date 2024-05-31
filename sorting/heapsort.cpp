#include <iostream>
#include <vector>
using namespace std;

void Heapify(vector<int>& arr, int size){
    // build a heap
    for(int i=size/2-1; i>=0; --i){
        // assign largest as root
        int largest = i;
        int left = 2*i+1, right = 2*i+2;

        // assign largest data
        if(left < size && arr[left] > arr[largest]){
            largest = left;
        }

        if(right < size && arr[right] > arr[largest]){
            largest = right;
        }

        // swap root with largest data and make a max heap
        if(largest != i){
            swap(arr[i], arr[largest]);
        }

        // create heap repeatly
        i = largest;
    }
}

void Heapsort(vector<int>& arr){
    int size = arr.size();
    Heapify(arr, size);
    
    for(int i=size-1; i>0; --i){
        swap(arr[0], arr[i]);
        Heapify(arr, i);
    }
}

void Output(vector<int>& arr){
    for(auto& it : arr)
        cout << it << " ";
    cout << endl;
}

int main(){
    vector<int> data = {26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    Heapsort(data);
    Output(data);

    return 0;
}