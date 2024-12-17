#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
int main() {
    ifstream file("in.txt");
    string line;
    if (file.is_open()) {
        // Read each line from the file and store it in the
        // 'line' variable.
        while (getline(file, line)) {
            cout << line << endl;
        }
        // Close the file stream once all lines have been
        // read.
        file.close();
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        cerr << "Unable to open file!" << endl;
    }
    // int sum = 0;
    // int i;string c;char r;
    // while(1) {
    //     scanf("%d, %c, %s",&i,&r,&c);
    //     if (i == -1){break;}
    //     if (!c.compare("right")) {sum+=i;}
    // }
    // cout<<sum;
    return 0;
}