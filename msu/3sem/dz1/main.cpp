#include "CPoly.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        int init[] = {2, 4, 3};
        CPoly poly(7, init, 3); 
        std::cout << "f(x) = " << poly << std::endl;

        std::cout << "x^2: " << poly[2] << std::endl;

        poly[2] = 10;
        std::cout << "x^2: " << poly[2] << std::endl;

        std::cout << "f(x) + (-1) = " << (poly + (-1)) << std::endl;

        std::cout << "f(x) + 1    = " << (poly + 1) << std::endl;

        std::cout << "2 + f(x)    = " << (2 + poly) << std::endl;

        std::cout << "f(x) + 4    = " << (poly + 4) << std::endl;

        std::cout << poly[N + 1] << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    }

    return 0;
}