#include <iostream>
#include <stdlib.h>
using namespace std;

void debug(){ //causes RE
    int *ptr = NULL;
    *ptr = 10;
}

class Miner{
public:
    char bag[105];
    int bagptr=0;
    char invent[105];
    int invptr=0, useptr=0;
    int maxL=0;
    void dig(int col);
    void use();
    void bomb(int col, int row);
    void clover(int col);
    void pig();
    void flash();
    void magnet();
};

int r, l, n;
char mine[105][205];
Miner miner;

int main(){
    scanf("%d %d %d", &r, &l, &n);
    miner.maxL=l;

    for(int i=l-1; i>=0; i--)
        for(int j=0; j<r; j++) cin >> mine[j][i];

    while(n--){
        string op;
        cin >> op;
        if(op=="DIG"){
            int col;
            scanf("%d", &col);
            miner.dig(col);
        }else if(op=="USE") miner.use();
    }

    // print bag
    printf("FINAL BAG:\n");
    for(int i=0; i<miner.bagptr; i++) printf("%c ", miner.bag[i]);
    printf("\n");
    

    //print map
    printf("FINAL MAP:\n");
    int maxt=-1;
    for(int i=miner.maxL-1; i>=0; i--)
        for(int j=0; j<r; j++)
            if(mine[j][i]!='_'){
                if(i>maxt) maxt=i;
                break;
            }
    miner.maxL=maxt+1;

    for(int i=miner.maxL-1; i>=0; i--){
        for(int j=0; j<r; j++){
            printf("%c ", mine[j][i]);
        }
        printf("\n");
    }

    return 0;
}

//OK
void Miner::dig(int col){
    int i;
    char temp;
    if(col>=r || col<0) return;

    for(i=maxL-1; i>=0; i--){
        if(mine[col][i]!='_'){
            temp=mine[col][i];
            mine[col][i]='_';
            break;
        }
    }

    switch(temp){
        case 'D': case 'G':
            bag[bagptr++]=temp;
            break;
        case 'B':
            bomb(col, i);
            break;
        case 'F': case 'M':
            invent[invptr++]=temp;
            break;
        case 'C':
            clover(col);
            break;
        case 'P':
            pig();
            break;
        default:
            return;
    }
}

//OK
void Miner::use(){
    if(useptr>=invptr) return;
    char op=invent[useptr++];
    switch(op){
        case 'F':
            flash();
            break;
        case 'M':
            magnet();
            break;
        default:
            return;
    }
}

//OK
void Miner::bomb(int col, int row){
    int dir[8][2]={{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    for(int i=0; i<8; i++){
        if(col+dir[i][0]<0 || col+dir[i][0]>=r || row+dir[i][1]<0 || row+dir[i][1]>=maxL) continue;
        mine[col+dir[i][0]][row+dir[i][1]]='_';
    } 
}

void Miner::clover(int col){
    char loot=bag[bagptr-1];
    int maxt=-1;
    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;
        for(int j=maxL-1; j>=0; j--){
            if(mine[i][j]!='_'){
                if(j>maxt) maxt=j;
                break;
            }
        }
    }

    if(maxt==-1 || bagptr<=0) return;

    for(int i=0; i<r; i++){
        mine[i][maxt+1]='_';
        mine[i][maxt+2]='_';
        mine[i][maxt+3]='_';
    }

    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;
        for(int j=0; j<3; j++){
            mine[i][maxt+j+1]=loot;
        }
    }

    if(maxL<maxt+4) maxL=maxt+4;
}

//OK
void Miner::pig(){
    while(bagptr>=0){
        if(bag[bagptr-1]=='D') break;
        bag[--bagptr]=0;
    }
    if(bagptr<0) {
        bagptr = 0;
    }
}

//OK
void Miner::flash(){
    int maxt=-1;
    for(int i=maxL-1; i>=0; i--){
        for(int j=0; j<r; j++){
            if(mine[j][i]!='_'){
                if(i>maxt) maxt=i;
                break;
            }
        }
    }

    if(maxt==-1){
        printf("MINE LEVEL:1\n");
        for(int j=0; j<r; j++) printf("_ ");
        printf("\n");
        maxL=0;
        return;
    }

    printf("MINE LEVEL:%d\n", maxt+1);
    for(int j=0; j<r; j++) printf("%c ", mine[j][maxt]);
    printf("\n");

    maxL=maxt+1;
}

//OK
void Miner::magnet(){
    for(int i=0; i<r; i++) dig(i);
}