#include <stdio.h>
void mystery(int *a, int *b) {
    int *c;
    c = b;
    b = a;
    a = c;
} // nothing happens as C function args are passed by values
void mystery2(int *a, int *b) {
    int temp = *a; // Save the value pointed to by `a`
    *a = *b;       // Assign the value pointed to by
                   // `b` to the location pointed to by `a`
    *b = temp;     // Assign the saved value to the
}                  // location pointed to by `b`
int main() {
    int a = 100, b = 500;
    int c = 300, d = 420;
    printf("%d %d %d %d\n", a, b, c, d);
    mystery(&a, &b);
    printf("%d %d %d %d\n", a, b, c, d);
    if (a < c) {
        mystery(&c, &a);
        printf("%d %d %d %d\n", a, b, c, d);
    }
    mystery(&a, &d);
    printf("%d %d %d %d\n", a, b, c, d);
}