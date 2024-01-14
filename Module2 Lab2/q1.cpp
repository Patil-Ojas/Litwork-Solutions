#include <iostream>

class MinimumNumbersSolution {
public:
    int findMinimumNumbers(int num, int k) {
        if (num == 0) return 0;
        for (int i = 1; i <= num; ++i) {
            int temp = num - k * i;
            if (temp >= 0 && temp % 10 == 0) return i;
        }
        return -1;
    }
};

int main() {
    MinimumNumbersSolution solution;

    int number, multiplier;
    std::cout << "Enter a number: ";
    std::cin >> number;

    std::cout << "Enter a multiplier: ";
    std::cin >> multiplier;

    int result = solution.findMinimumNumbers(number, multiplier);

    if (result == -1) {
        std::cout << "No solution found." << std::endl;
    } else {
        std::cout << "Minimum numbers needed: " << result << std::endl;
    }

    return 0;
}
