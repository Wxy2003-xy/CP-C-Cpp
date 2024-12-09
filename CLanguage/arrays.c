#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    char arr[10];
    int i;
    for (i = 0; i < 3; i++) {
        arr[i] = 'a';
    }
    arr[9] = '\0'; // Null-terminate the string
    printf("%lu", strlen(arr)); // undefined behaviour!

    char *str = malloc(10 * sizeof(char));
    printf("%lu", strlen(str)); 
    return 0;
}