#include<iostream>
using namespace std;
int main(){
    int x;
    cin>>x;
    int i;
    for(i=1;i<=x;i++){
        int a,b;
        cin>>a>>b;
        cout<<i<<" "<<(b*b+b)/2<<" "<<(((4*b*b+2*b)/2-b)/2)<<" "<<(((4*b*b+2*b)/2+b)/2)<<endl;
    }
}
