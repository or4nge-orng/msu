#include "CPoly.h"
#include <iostream>

int main() {
    try {
        std::cout << "=== Тестирование CPoly ===\n";

        // 1. Конструктор от массива
        int init[] = {2, 4, 3}; // 3x^2 + 4x + 2
        CPoly p1(init, 3, 5);
        std::cout << "p1 = " << p1 << "\n";

        // 2. Конструктор по умолчанию
        CPoly p2;
        std::cout << "p2 (default) = " << p2 << "\n";

        // 3. Копирование
        CPoly p3 = p1;
        std::cout << "p3 (copy of p1) = " << p3 << "\n";

        // 4. Перемещение
        CPoly p4 = std::move(p3);
        std::cout << "p4 (move from p3) = " << p4 << "\n";
        std::cout << "p3 after move = " << p3 << "\n";

        // 5. Присваивание копированием
        p2 = p1;
        std::cout << "p2 = p1 -> " << p2 << "\n";

        // 6. Присваивание перемещением
        CPoly p5;
        p5 = std::move(p2);
        std::cout << "p5 = move(p2) -> " << p5 << "\n";
        std::cout << "p2 after move = " << p2 << "\n";

        // 7. Унарный плюс (дифференцирование rvalue)
        std::cout << "\nУнарный плюс:\n";
        CPoly p6 = +CPoly(init, 3, 5);
        std::cout << "+CPoly(init,3,5) = " << p6 << "\n";

        // 8. Инкремент/декремент
        std::cout << "\nИнкремент/декремент:\n";
        CPoly p7(init, 3, 5);
        std::cout << "p7 = " << p7 << "\n";
        ++p7;
        std::cout << "++p7 = " << p7 << "\n";
        p7++;
        std::cout << "p7++ = " << p7 << "\n";
        --p7;
        std::cout << "--p7 = " << p7 << "\n";
        p7--;
        std::cout << "p7-- = " << p7 << "\n";

        // 9. Сложение и вычитание
        std::cout << "\nСложение и вычитание:\n";
        int init2[] = {1, 1, 1}; // x^2 + x + 1
        CPoly p8(init2, 3, 5);
        std::cout << "p7 = " << p7 << "\n";
        std::cout << "p8 = " << p8 << "\n";
        std::cout << "p7 + p8 = " << (p7 + p8) << "\n";
        std::cout << "p7 - p8 = " << (p7 - p8) << "\n";

        // 10. Исключение при интегрировании
        std::cout << "\nИсключение при ++ для x^4 в Z_5:\n";
        int init3[] = {0, 0, 0, 0, 1}; // x^4
        CPoly p9(init3, 5, 5);
        std::cout << "p9 = " << p9 << "\n";
        std::cout << "Вызов ++p9...\n";
        ++p9; // должно выбросить исключение
        std::cout << "Это не должно вывестись.\n";

    } catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << "\n";
    }
    return 0;
}