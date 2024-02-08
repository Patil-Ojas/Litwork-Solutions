#include <iostream>
#include <vector>
#include <algorithm> // for std::max

int calculateMaxValue(std::vector<int>& arr, int sz) {
    int maxVal = arr[1];
    for (int i = 2; i <= sz; ++i) {
        arr[i] += arr[i - 1];
        maxVal = std::max(maxVal, arr[i]);
    }
    return maxVal;
}

int main() {
    int size, queries;
    std::cin >> size >> queries;
    std::vector<int> arr(size + 1, 0);

    for (int i = 0; i < queries; ++i) {
        int left, right, value;
        std::cin >> left >> right >> value;
        arr[left] += value;
        if (right + 1 <= size) {
            arr[right + 1] -= value;
        }
    }

    int maxVal = calculateMaxValue(arr, size);

    std::cout << maxVal << std::endl;
    return 0;
}
