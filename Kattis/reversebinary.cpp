#include<iostream>
#include<ctype.h>
using namespace std;
int main(){
    uint32_t x;
    cin>>x;
    uint32_t y=0;
    while(x > 0) {
        if (x%2!=0){y=y|0b1;y=y<<1;}
        else{y=y<<1;}
        x=x>>1;
    }
    y=y>>1;
    cout<<y;
}

// 101111 --> 111101
//1101 -> 10110