#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int main(){
    long double x;
    long double y;
    cin>>x;
    y=sqrt(x);
    y = y * 4;

    // cout<<fixed<<setprecision(20)<<4*y;
    printf("%.16lf", y);
}
//8.94427190999915922021    
//8.94427190999915878564    
//8.94427204132080078125    