#include <iostream>
#include <stdexcept>
#include "Vector3.h"

int main() {
    Vector3 a(0, 0, 0, 1, 2, 3);
    Vector3 b(0, 0, 0, 4, 5, 6);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "a + b = " << a + b << "\n";    // (5, 7, 9)
    std::cout << "a - b = " << a - b << "\n";    // (-3, -3, -3)
    std::cout << "a * b = " << a * b << "\n";    // (-3, 6, -3)
    std::cout << "a * 2 = " << a * 2 << "\n";    // (2, 4, 6)
    std::cout << "3 * a = " << 3 * a << "\n";    // (3, 6, 9)
    std::cout << "b / a = " << b / a << "\n";    // (4, 2.5, 2)
    std::cout << "dot = " << a.dot(b) << "\n";   // 32
    std::cout << "cos = " << (a ^ b) << "\n";    // 0.974632
    std::cout << "a < b: " << (a < b) << ", a == b: " << (a == b) << "\n";

    Vector3 c = a;      // копирование
    c += b;
    std::cout << "c = " << c << "\n";

    try {
        Vector3 zero;
        std::cout << (a / zero) << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "mistake: " << e.what() << "\n";
    }

    std::cout << "enter vector (x1 y1 z1 x2 y2 z2): ";
    Vector3 v;
    if (std::cin >> v) std::cout << "length = " << v.length() << "\n";
    return 0;
}