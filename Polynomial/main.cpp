#include "Polynomial.h"
#include <iostream>
#include <stdexcept>

int main() {
    Polynomial p, q;
    std::cout << "Format vvoda i vyvoda: stepen a0 a1 ... an.\n"
              << "Primer: 2 -1 0 1 zadaet x^2 - 1.\nVvedite P: ";

    if (!(std::cin >> p)) {
        std::cerr << "Oshibka vvoda P.\n";
        return 1;
    }

    std::cout << "Vvedite Q: ";
    if (!(std::cin >> q)) {
        std::cerr << "Oshibka vvoda Q.\n";
        return 1;
    }

    std::cout << "P + Q = " << p + q << "\nP - Q = " << p - q
              << "\nP * Q = " << p * q << '\n';

    try {
        const Polynomial quotient = p / q;
        std::cout << "P / Q = " << quotient << '\n';
    } catch (const std::domain_error&) {
        std::cout << "Delenie na nulevoi mnogochlen nevozmozhno.\n";
    }

    std::cout << "Vvedite x dlya vychisleniya P(x): ";
    double x;
    if (!(std::cin >> x)) {
        std::cerr << "Oshibka vvoda x.\n";
        return 1;
    }

    std::cout << "P(x) = " << p(x) << '\n';
}