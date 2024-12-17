#include<iostream>
using namespace std;
int main(){
    int x;cin>>x;
    if (x == 0){
        std::cout<<"++\n++\n"; return 0;
    }
    cout<<"+";
    int i,j;
    for (i = 0;i<x;i++){cout<<"-";}
    cout<<"+\n";
    
    for (j = 0;j<x;j++){cout<<"|";for(i = 0;i<x;i++){cout<<" ";}cout<<"|\n";}
    cout<<"+";
    
    for (i = 0;i<x;i++){cout<<"-";}
    cout<<"+\n";
    return 0;
}