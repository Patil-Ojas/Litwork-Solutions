#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

class Trimmer {
public:
    std::vector<int> findSmallestTrimmedNumbers(const std::vector<std::string>& numbers, const std::vector<std::vector<int>>& queries) {
        std::vector<int> result;
        for (const auto& query : queries) {
            std::priority_queue<std::pair<std::string, int>> minHeap;
            for (int i = 0; i < numbers.size(); ++i) {
                int trimLength = numbers[i].length() - query[1];
                std::string trimmedSuffix = numbers[i].substr(trimLength, query[1]);
                if (minHeap.size() < query[0]) {
                    minHeap.push({trimmedSuffix, i});
                } else {
                    if (minHeap.top().first > trimmedSuffix) {
                        minHeap.pop();
                        minHeap.push({trimmedSuffix, i});
                    }
                }
            }
            int smallestIndex = minHeap.top().second;
            result.push_back(smallestIndex);
        }
        return result;
    }
};

int main() {
    Trimmer trimmer;

    std::vector<std::string> numbers;
    std::string inputNumbers;
    std::getline(std::cin, inputNumbers);
    std::stringstream ssNumbers(inputNumbers);
    std::string tempNumber;
    while (ssNumbers >> tempNumber) {
        numbers.push_back(tempNumber);
    }

    int numQueries;
    std::cin >> numQueries;
    std::vector<std::vector<int>> queries(numQueries, std::vector<int>(2));
    for (int i = 0; i < numQueries; ++i) {
        std::cin >> queries[i][0] >> queries[i][1];
    }

    std::vector<int> resultIndices = trimmer.findSmallestTrimmedNumbers(numbers, queries);

    for (int index : resultIndices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return 0;
}
