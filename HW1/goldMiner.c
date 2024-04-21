#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char bag[105];
    int bagptr;
    char invent[105];
    int invptr, useptr;
    
}Miner;

int r, l, n;
char mine[105][205];
Miner miner;


void dig(int col);
void use();
void bomb(int col, int row);
void clover(int col);
void pig();
void flash();
void magnet();

int main(){
    scanf("%d %d %d", &r, &l, &n);
    miner.bagptr=0, miner.invptr=0, miner.useptr=0;

    for(int i=0; i<l; i++){
        for(int j=0; j<r; j++){
            scanf(" %c", &mine[j][i]);
        }
    }

    while(n--){
        char op;
        scanf(" %c", &op);
        if(op=='D'){
            int col;
            scanf("%d", &col);
            dig(col);
        }else if(op=='U') use();

        // print map
        for(int i=0; i<l; i++){
            for(int j=0; j<r; j++){
                printf("%c ", mine[j][i]);
            }
            printf("\n");
        }
    }

    // print bag
    printf("FINAL BAG:\n");
    for(int i=0; i<miner.bagptr; i++) printf("%c ", miner.bag[i]);
    printf("\n");

    //print map
    printf("FINAL MAP:\n");
    for(int i=0; i<l; i++){
        for(int j=0; j<r; j++){
            printf("%c ", mine[j][i]);
        }
        printf("\n");
    }

    return 0;
}

void dig(int col){
    int i;
    char temp;
    if(col>=r) return;

    for(i=l-1; i>=0; i--){
        if(mine[col][i]!='_'){
            temp=mine[col][i];
            mine[col][i]='_';
            break;
        }
    }

    switch(temp){
        case 'D': case 'G':
            miner.bag[miner.bagptr++]=temp;
            break;
        case 'B':
            bomb(col, i);
            break;
        case 'F': case 'M':
            miner.invent[miner.invptr++]=temp;
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

void use(){
    if(miner.useptr>=miner.invptr) return;
    char op=miner.invent[miner.useptr++];
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

void bomb(int col, int row){
    int dir[8][2]={{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    for(int i=0; i<8; i++){
        if(col+dir[i][0]<0 || col+dir[i][0]>=r || row+dir[i][1]<0 || row+dir[i][1]>=l) continue;
        mine[col+dir[i][0]][row+dir[i][1]]='_';
    } 
}

void clover(int col){
    char loot=miner.bag[miner.bagptr-1];
    int maxt=-1;
    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;
        for(int j=l-1; j>=0; j--){
            if(mine[i][j]!='_'){
                if(j>maxt) maxt=j;
                break;
            }
        }
    }

    if(maxt=-1) return;

    for(int i=col-2; i<=col+2; i++){
        if(i<0 || i>=r) continue;
        for(int j=0; j=3; j++){
            mine[i][maxt+j]=loot;
        }
    }

    l= l>maxt+3 ? l:maxt+3;
}

void pig(){
    while(1){
        if(miner.bag[miner.bagptr-1]=='D') break;
        miner.bag[miner.bagptr--]=0;
    }
}

void flash(){
    int i;
    for(i=l-1; i>=0; i--){
        for(int j=0; j<r; j++){
            if(mine[j][i]!='_') break;
        }
    }

    if(i==-1){
        printf("MINE LEVEL:1\n");
        for(int j=0; j<r; j++) printf("_ ");
        printf("\n");
        return;
    }

    printf("MINE LEVEL:%d\n", i);
    for(int j=0; j<r; j++) printf("%c ", mine[j][i]);
    printf("\n");
}

void magnet(){
    for(int i=0; i<r; i++) dig(i);
}