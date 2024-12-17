#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
int find(int a,int b){
    if(a%b==0){
        return pow(2,a)-1;
    }
    if (b%a==0){
        return pow(2,b-1);
    }
    float fibo = 2.078087 * log(a+b) + 1.672276;
    int l=ceil(fibo)-3;
    int up=pow(2,l)-1;
    l++;
    return 0;
}

int getIdx(int a,int b){
    if(a==b){
        return 1;
    }
    if(b==1){
        return pow(2,a)-1;
    }
    if (a==1){
        return pow(2,b-1);
    }
    if(a>b){
        int r;
        int i = getIdx(a-b,b);
        int li = floor(log2(i));
        int ofst = i - pow(2,li);
        int abv = pow(2,li+1);
        r = abv+ofst*2;
        return r+1;
    }else{
        int r;
        int i = getIdx(a,b-a);
        int li = floor(log2(i));
        int ofst = i - pow(2,li);
        int abv = pow(2,li+1);
        r = abv+ofst*2;
        return r;
    }
}
int main(){
    int x;
    scanf("%d",&x);
    int i;
    for (i=0;i<x;i++){
        int m,n,d;
        char slash;
        cin>>m>>n>>slash>>d;
        cout<<(i+1)<<" "<<getIdx(n,d)<<endl;
    }
    return 0;   
}

