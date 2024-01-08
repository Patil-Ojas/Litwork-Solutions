#include <iostream>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int findLongestUniqueSubstring(const std::string& inputString) {
        int length = inputString.size();
        int maxLength = 0;
        std::unordered_set<char> charSet;
        int leftIndex = 0;
        
        for (int rightIndex = 0; rightIndex < length; ++rightIndex) {
            while (charSet.find(inputString[rightIndex]) != charSet.end()) {
                charSet.erase(inputString[leftIndex]);
                ++leftIndex;
            }
            charSet.insert(inputString[rightIndex]);
            maxLength = std::max(maxLength, rightIndex - leftIndex + 1);
        }
        
        return maxLength;
    }
};

int main() {
    Solution solution;

    std::string userInput;
    std::cout << "Enter a string: ";
    std::cin >> userInput;
    
    int result = solution.findLongestUniqueSubstring(userInput);
    std::cout<< result << std::endl;
    
    return 0;
}
