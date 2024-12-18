/**
 * Given an array of consecutive positive integers from 1 to n.
 * Every element can swap with its left neighbour.
 * We wish to perform such swaps repeatedly to achieve
 * a permutation q such that every element is swapped to its left at most twice.
 * Compute the minimum number of swaps if this is possible.
 * in:  [1,2,3,4,5]
 *      |   1
 *      [1,3,2,4,5]
 *      |   2
 *      [3,1,2,4,5]
 *      |   3
 * out: [3,1,2,5,4]
 * re: 3
*/


#include<iostream>
#include<vector>
using namespace std;
void swap(int* array, int index){
    if(index==0){return;}
    int tmp = array[index];
    array[index]=array[index-1];
    array[index-1]=tmp;
}
int main(){
    int n;
    cin>>n;
    int array[n];
    for (int i=0;i<n;i++){array[i]=i+1;}

}