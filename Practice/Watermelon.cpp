#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n > 2 && n % 2 == 0) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    } 

    return 0;
}
