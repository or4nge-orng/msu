#include <iostream>
#include <cmath>
#include <string>
int main() {
    int col1, row1, col2, row2;
    std::string result;

    std::cin >> col1 >> row1 >> col2 >> row2;

    if (std::abs(col1 - col2) == std::abs(row1 - row2) || col1 == col2 || row1 == row2) {
        result = "YES";
    } else {
        result = "NO";
    }
    std::cout << result << "\n";
}