#include <iostream>

const int MOD = 1000000007;
const int MAX_SIZE = 1000;

long long combinations[MAX_SIZE + 1][MAX_SIZE + 1];
long long backwardSum[MAX_SIZE + 1], resultSequence[MAX_SIZE + 1];

void calculateCombinations() {
    combinations[1][0] = 1;
    for (int j = 1; j <= MAX_SIZE; j++) {
        combinations[1][j] = combinations[1][j - 1];
        if (j >= 2) combinations[1][j] = (combinations[1][j] + combinations[1][j - 2]) % MOD;
        if (j >= 3) combinations[1][j] = (combinations[1][j] + combinations[1][j - 3]) % MOD;
        if (j >= 4) combinations[1][j] = (combinations[1][j] + combinations[1][j - 4]) % MOD;
    }
    for (int i = 2; i <= MAX_SIZE; i++) {
        for (int j = 1; j <= MAX_SIZE; j++) {
            combinations[i][j] = (combinations[i - 1][j] * combinations[1][j]) % MOD;
        }
    }
}

int main() {
    calculateCombinations();
    int rows, columns;
    std::cin >> rows >> columns;
    backwardSum[1] = 0;
    resultSequence[1] = 1;
    for (int j = 2; j <= columns; j++) {
        backwardSum[j] = 0;
        for (int k = 1; k < j; k++) {
            backwardSum[j] = (backwardSum[j] + (combinations[rows][j - k] * resultSequence[k]) % MOD) % MOD;
        }
        resultSequence[j] = (combinations[rows][j] + MOD - backwardSum[j]) % MOD;
    }
    std::cout << resultSequence[columns] << std::endl;
    return 0;
}
