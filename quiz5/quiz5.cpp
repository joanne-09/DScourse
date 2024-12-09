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

// by copilot

// SOLUTION: using merge sort
// #include <bits/stdc++.h>
// using namespace std;

// long long inversion_count = 0;

// void merge(vector<int>& arr, int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;

//     // Temporary arrays
//     vector<int> L(n1);
//     vector<int> R(n2);

//     // Copy data to temp arrays
//     for(int i = 0; i < n1; ++i)
//         L[i] = arr[left + i];
//     for(int j = 0; j < n2; ++j)
//         R[j] = arr[mid + 1 + j];

//     // Merge the temp arrays back into arr[left..right]
//     int i = 0; // Initial index of first subarray
//     int j = 0; // Initial index of second subarray
//     int k = left; // Initial index of merged subarray

//     while(i < n1 && j < n2) {
//         if(L[i] <= R[j]) {
//             arr[k++] = L[i++];
//         } else {
//             arr[k++] = R[j++];
//             inversion_count += n1 - i; // Count inversions
//         }
//     }

//     // Copy the remaining elements of L[], if any
//     while(i < n1)
//         arr[k++] = L[i++];

//     // Copy the remaining elements of R[], if any
//     while(j < n2)
//         arr[k++] = R[j++];
// }

// void mergeSort(vector<int>& arr, int left, int right) {
//     if(left >= right)
//         return;
    
//     int mid = left + (right - left) / 2;
//     mergeSort(arr, left, mid);       // Sort first half
//     mergeSort(arr, mid + 1, right);  // Sort second half
//     merge(arr, left, mid, right);    // Merge the sorted halves
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n;
//     cin >> n;
//     vector<int> p(n);
//     for(int i = 0; i < n; ++i)
//         cin >> p[i];
    
//     inversion_count = 0;
//     mergeSort(p, 0, n - 1);

//     cout << inversion_count << '\n';
//     return 0;
// }

// SOLUTION: using BIT tree
// #include <bits/stdc++.h>
// using namespace std;

// // Fenwick Tree Implementation for Inversion Count
// class BIT{
//     int n;
//     vector<int> bit;
// public:
//     void init(int _n){
//         n = _n;
//         bit.assign(n + 1, 0);
//     }
//     void update(int x, int val){
//         for(; x <= n; x += x & -x)
//             bit[x] += val;
//     }
//     int query(int x) const {
//         int sum = 0;
//         for(; x > 0; x -= x & -x)
//             sum += bit[x];
//         return sum;
//     }
// };

// int main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n;
//     cin >> n;
//     vector<int> p(n);
//     for(int i = 0; i < n; ++i)
//         cin >> p[i];

//     // Initialize BIT with size equal to the maximum value in p
//     BIT tree;
//     tree.init(n);

//     long long inversion_count = 0;
//     for(int i = n - 1; i >= 0; --i){
//         inversion_count += tree.query(p[i] - 1); // Number of elements less than p[i]
//         tree.update(p[i], 1); // Increase count of p[i]
//     }

//     cout << inversion_count << '\n';
//     return 0;
// }
