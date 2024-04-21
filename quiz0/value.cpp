#include <stdio.h>

typedef struct{
    int val;
    int wei;
}Node;

Node node[15];
int n, k, min=1000000000;

int rec(int v, int w, int idx){
    if(k<=v && min>w) min=w;
    else{
        for(int i=idx; i<n; i++){
            rec(v+node[i].val, w+node[i].wei, i+1);
        }
    }
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i=0; i<n; i++){
        scanf("%d %d", &node[i].val, &node[i].wei);
    }
    rec(0, 0, 0);

    printf("%d\n", min);
    return 0;
}