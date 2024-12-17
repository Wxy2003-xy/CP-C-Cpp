#include<iostream>
#include<string.h>
int main(){
    std::string s;
    std::getline(std::cin, s);
    int l = s.length();
    std::cout<<l;
    return 0;
}