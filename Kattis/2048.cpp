#include<bits/stdc++.h>

using namespace std;

void swipe(int table[4][4], int dir) {
    if (dir == 0) { //left
        for (int i = 0; i < 4; i++) {
            for (int a = 0; a < 4; a++) {
                for (int j = 1; j < 4; j++) {
                    if (table[i][j] == 0 || table[i][j] == table[i][j - 1]) {
                        table[i][j - 1] += table[i][j];
                        for (int k = j; k < 4; k++) {
                            if (k == 3) {
                                table[i][k] = 0;
                            } else {
                            table[i][k] = table[i][k+1];

                            }
                        }
                    }
                }
            }
            for (int l = 0; l < 4; l++) {
                cout<<table[i][l]<<" ";
            }
            cout<<"\n";
        }
    }
    if (dir == 1) { //up
        for (int i = 0; i < 4; i++) {
            for (int a = 0; a < 4; a++) {
                for (int j = 1; j < 4; j++) {
                    if (table[j][i] == 0 || table[j][i] == table[j - 1][i]) {
                        table[j-1][i] += table[j][i];
                        for (int k = j; k < 4; k++) {
                            if (k == 3) {
                                table[k][i] = 0;
                            } else {
                                table[k][i] = table[k+1][i];

                            }
                        }
                    }
                }
            }
            for (int l = 0; l < 4; l++) {
                cout<<table[i][l]<<" ";
            }
            cout<<"\n";
        }
    }
    if (dir == 2) { //right
        for (int i = 0; i < 4; i++) {
            for (int a = 3; a >= 0; a--) {
                for (int j = 3; j >=0; j--) {
                    if (table[i][j] == 0 || table[i][j] == table[i][j - 1]) {
                        table[i][j - 1] += table[i][j];
                        for (int k = j; k >=0; k--) {
                            if (k == 0) {
                                table[i][k] = 0;
                            } else {
                            table[i][k] = table[i][k-1];

                            }
                        }
                    }
                }
            }
            for (int l = 0; l < 4; l++) {
                cout<<table[i][l]<<" ";
            }
            cout<<"\n";
        }
    }
    if (dir == 3) { //down
        for (int i = 0; i < 4; i++) {
            
        }
    }
    return ;
}

void up(int** x) {
    for (int col = 0; col < 4; col++) {
        
    }
}

int main() {
    int x[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin>>x[i][j];
        }
    }
    swipe(x, 2);

}