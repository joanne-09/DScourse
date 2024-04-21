#include <iostream>
#include <vector>
#include <string>
using namespace std;

int idx = 0, len = 0;
string op;
vector<vector<char>> original;

void insert(string in);
void shift();
void reverse();
void trans();
void print();

int main(){
    while((cin >> op) && !cin.eof()){
        if(op == "Insert"){
            string notation;
            cin >> notation;

            insert(notation);
        }else if(op == "Shift"){
            shift();
        }else if(op == "Reverse"){
            reverse();
        }else if(op == "Print"){
            print();
        }else if(op == "Transpose"){
            trans();
        }
    }

    return 0;
}

void insert(string in){
    if(idx == 0) len = in.length();
    vector<char> temp;

    for(int i=0; i<len; i++){
        // set original matrix
        temp.push_back(in[i]);
    }

    original.push_back(temp);
    idx ++;
}

void shift(){
    int i; char c;
    cin >> i >> c;

    for(int j=0; j<len-1; j++){
        original[i][j] = original[i][j+1];

    }

    original[i][len-1] = c;
}

void reverse(){
    int i;
    cin >> i;

    int temp = len/2;
    for(int j=0; j<temp; j++){
        char t = original[i][j];
        original[i][j] = original[i][len-j-1];
        original[i][len-j-1] = t;
    }
}

void trans(){
    for(int i=0; i<len; i++){
        for(int j=0; j<idx; j++){
            cout << original[j][i] << " ";
        }
        cout << endl;
    }
}

void print(){
    for(int i=0; i<idx; i++){
        for(int j=0; j<len; j++){
            cout << original[i][j] << " ";
        }
        cout << endl;
    }
    
}