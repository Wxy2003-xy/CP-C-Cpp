#include<iostream>
#include<math.h>
int main(){
    int x;
    std::cin>>x;
    if (x<=2){std::cout<<x;return 0;} else {int y=(int)ceil(log2(x)) + 1;std::cout<<y;return 0;}
}