#include <iostream>

class ClumsyCalculator {
public:
    int calculate(int inputNumber) {
        if (inputNumber == 1)
            return 1;
        if (inputNumber == 2)
            return 2;
        if (inputNumber == 3)
            return 6;
        if (inputNumber == 4)
            return 7;
        if (inputNumber % 4 == 1)
            return inputNumber + 2;
        if (inputNumber % 4 == 2)
            return inputNumber + 2;
        if (inputNumber % 4 == 3)
            return inputNumber - 1;
        return inputNumber + 1;
    }
};

int main() {
    ClumsyCalculator clumsyCalc;
    int userNumber;
    std::cin >> userNumber;
    int clumsyResult = clumsyCalc.calculate(userNumber);
    std::cout << clumsyResult << std::endl;

    return 0;
}
