#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    float fibo = 2.078087 * log(n) + 1.672276;
    int r = ceil(fibo);
    cout<<r<<endl;;
    int x = floor(log2(5));
    cout<<x;
}