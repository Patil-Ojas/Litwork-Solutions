#include <iostream>
#include <vector>
#include <deque>
#include <sstream>

std::vector<int> modifiedSlidingSubarrayBeauty(std::vector<int>& array, int windowSize, int extensionSize) {
    std::vector<int> result;
    std::deque<int> deque;

    for (int i = 0; i < array.size(); ++i) {
        while (!deque.empty() && deque.front() < i - windowSize + 1) {
            deque.pop_front();
        }

        while (!deque.empty() && array[deque.back()] > array[i]) {
            deque.pop_back();
        }

        deque.push_back(i);

        if (i >= windowSize - 1) {
            result.push_back(array[deque.front() + extensionSize - 1]);
        }
    }

    return result;
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<int> inputArray;
    int number;
    while (ss >> number) {
        inputArray.push_back(number);
    }

    int windowSize, extensionSize;
    std::cin >> windowSize >> extensionSize;

    std::vector<int> result = modifiedSlidingSubarrayBeauty(inputArray, windowSize, extensionSize);

    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}
