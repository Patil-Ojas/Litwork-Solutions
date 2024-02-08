#include <iostream>

void egyptianFraction(int numerator, int denominator) {
    if (denominator == 0 || numerator == 0) {
        return;
    }
    if (denominator % numerator == 0) {
        std::cout << denominator / numerator << std::endl;
        return;
    }
    if (numerator % denominator == 0) {
        std::cout << numerator / denominator << std::endl;
        return;
    }
    if (numerator > denominator) {
        std::cout << numerator / denominator << std::endl;
        egyptianFraction(numerator % denominator, denominator);
        return;
    }
    int x = denominator / numerator + 1;
    std::cout << x << std::endl;
    egyptianFraction(numerator * x - denominator, denominator * x);
}

int main() {
    int userNumerator, userDenominator;
    std::cout << "Enter the numerator: ";
    std::cin >> userNumerator;
    std::cout << "Enter the denominator: ";
    std::cin >> userDenominator;

    egyptianFraction(userNumerator, userDenominator);

    return 0;
}
